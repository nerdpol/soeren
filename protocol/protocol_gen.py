#!/usr/bin/python3
# generate c and python code for protocol from yaml definition

import yaml
import argparse

ap = argparse.ArgumentParser()
ap.add_argument("definition", default="protocol.yaml")
ap.add_argument("c_header", default="protocol.h")
ap.add_argument("c_source", default="protocol.c")
ap.add_argument("python", default="protocol.py")
args = ap.parse_args()

with open(args.definition, 'r') as f:
  packet_types = yaml.load(f)

with open(args.c_header, 'w') as f:
  f.write("/* THIS FILE IS GENERATED, DO NOT EDIT BY HAND */\n\n#ifndef SOEREN_RADIO_PACKET_H_\n#define SOEREN_RADIO_PACKET_H_\n\n#include <stdint.h>\n\nenum {\n")

  for p, packet_type in packet_types.items():
    f.write(f"  PKT_{p.upper()} = '{packet_type['char']}',\n")
  f.write("};\n\n")

  f.write("union __attribute__((packed)) packet {\n  uint8_t tag;\n")
  for p, packet_type in packet_types.items():
    f.write("  struct __attribute__((packed)) {\n    uint8_t tag;\n")
    for field in packet_type["fields"]:
      if "length" in field:
        f.write(f"    {field['type']} {field['name']}[{field['length']}];\n")
      else:
        f.write(f"    {field['type']} {field['name']};\n")
    f.write(f"  }} {p};\n")
  f.write("  uint8_t bytes[0];\n};\n\n")

  f.write("uint32_t radio_packet_size(uint8_t id);\n\n#endif\n")

with open(args.c_source, 'w') as f:
  f.write("/* THIS FILE IS GENERATED, DO NOT EDIT BY HAND */\n\n#include \"protocol.h\"\n\n")

  f.write("uint32_t radio_packet_size(uint8_t id) {\n  switch(id) {\n")
  for p in packet_types:
    f.write(f"    case PKT_{p.upper()}: return sizeof(packet.{p});\n")
  f.write("    default: return 0;\n  }\n}\n")

type_sizes = {"uint8_t": 1, "int8_t": 1, "char": 1, "uint16_t": 2, "int16_t": 2, "uint32_t": 4, "int32_t": 4, "float": 4}
def field_size(field):
  return type_sizes[field["type"]] * field.get("length", 1)

type_specifiers = {"uint8_t": 'B', "int8_t": 'b', "char": 'c', "uint16_t": 'H', "int16_t": 'h', "uint32_t": 'L', "int32_t": 'l', "float": 'f'}

with open(args.python, 'w') as f:
  f.write("# THIS FILE IS GENERATED, DO NOT EDIT BY HAND\n\nimport struct\n\n")
  
  # Lengths
  f.write("def radio_packet_size(id):\n\treturn {\n")
  for p, packet_type in packet_types.items():
    packet_type["size"] = sum(field_size(field) for field in packet_type["fields"])
    f.write(f"\t\tb'{packet_type['char']}': {packet_type['size']},\n")
  f.write("\t}.get(id, None)\n\n")

  # Parsing
  f.write("def radio_packet_parse(packet):\n")
  for p, packet_type in packet_types.items():
    f.write(f'\tif packet[0:1] == b"{packet_type["char"]}":\n')
    field_names = ['_type']
    field_specs = ['c']
    field_decodes = [f'"{p}"']
    field_encodes = [f'b"{packet_type["char"]}"']
    for field in packet_type["fields"]:
      if field["type"] == "char" and "length" in field:
        field_specs.append(f"{field['length']}s")
        field_names.append(field["name"])
        field_decodes.append(field["name"] + ".decode()")
        field_encodes.append(f"message['{field['name']}'].encode()")
      elif "length" in field:
        field_specs.append(f"{field['length']}{type_specifiers[field['type']]}")
        field_names.extend(f"{field['name']}{i}" for i in range(field["length"]))
        field_decodes.extend(f"{field['name']}{i}" for i in range(field["length"]))
        field_encodes.extend(f"message['{field['name']}{i}']" for i in range(field["length"]))
      else:
        field_specs.append(type_specifiers[field['type']])
        field_names.append(field["name"])
        field_decodes.append(field["name"])
        field_encodes.append(f"message['{field['name']}']")
    f.write("\t\t" + ','.join(field_names) + ", = struct.unpack('!" + "".join(field_specs) + "', packet)\n")
    field_entries = ", ".join(f'"{n}": {d}' for n, d in zip(field_names, field_decodes))
    f.write(f"\t\treturn {{{field_entries}}}\n")
    packet_type['_vars'] = field_names
    packet_type['_specs'] = field_specs
    packet_type['_encodes'] = field_encodes
  f.write("\n")

  # Packing
  f.write("def radio_packet_pack(message):\n")
  for p, packet_type in packet_types.items():
    f.write(f'\tif message["_type"] == "{p}":\n')
    f.write(f"\t\treturn struct.pack('!" + "".join(packet_type['_specs']) + "', " + ", ".join(packet_type['_encodes']) + ")\n")
  f.write('\telse:\n\t\traise ValueError("Unknown packet type")\n\n')