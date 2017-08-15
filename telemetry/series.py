import os
import mmap
import struct
import json

class Series:
	def __del__(self):
		self.close()

	def _cursor(self, t):
		'''Get the index of the point for t, or the index where it would be inserted'''
		if len(self) == 0:
			return None
		if t > self[len(self)-1][0]:
			return len(self)-1
		lo = 0
		hi = len(self)
		while lo < hi:
			mid = (lo+hi)//2
			if self[mid][0] < t:
				lo = mid+1
			else:
				hi = mid
		return lo

	def at(self, t):
		'''get the closest data point to t, or None if there are no data points'''
		i = self._cursor(t)
		points = self[i-1:i+1]
		if len(points) == 0:
			return None
		elif len(points) == 1:
			return points[0]
		p0, p1 = points
		if (p0[0] == p1[0]):
			return p0
		f = (t - p0[0]) / (p1[0] - p0[0])
		g = 1 - f
		result = tuple(f*p1[i] + g*p0[i] for i in range(len(p1)))
		return result

	def closest(self, t):
		'''get the closest data point to t, or None if there are no data points'''
		if len(self) == 0:
			return None
		i = self._cursor(t)
		if i == len(self) or abs(self[i-1][0] - t) <= abs(self[i][0] - t):
			return self[i-1]
		else:
			return self[i]

	def iter(self, tclip):
		'''iterate over all points tclip.min <= point.time < tclip.max'''
		t0, t1 = tclip
		i0 = self._cursor(t0)
		for v in self[i0:]:
			yield v
			if v[0] >= t1:
				break

	def append(self, *args):
		raise NotImplementedError()

	def close(self):
		pass

	def __delitem__(self, i):
		raise RuntimeError()


class SeriesMmap(Series):
	def __init__(self, filename, format):
		super().__init__()
		self.filename = filename
		self.format = format
		self._entrylen = struct.calcsize(self.format)
		self._fd = os.open(self.filename, os.O_RDWR|os.O_CREAT)
		self._mmap = None
		self.refresh()

	def refresh(self):
		size = os.fstat(self._fd).st_size
		if size == 0:
			os.write(self._fd, b'\x00')
			size = 1
		if not self._mmap:
			self._mmap = mmap.mmap(self._fd, size)
		else:
			self._mmap.resize(size)

	def __getitem__(self, i):
		if isinstance(i, slice):
			start, stop, step = i.indices(len(self))
			return [self[i_] for i_ in range(start, stop, step)]
		else:
			return struct.unpack(self.format, self._mmap[i*self._entrylen:(i+1)*self._entrylen])

	def __setitem__(self, i, value):
		if isinstance(i, slice):
			start, stop, step = i.indices(len(self))
			for j, i in enumerate(range(start, stop, step)):
				self._mmap[i*self._entrylen:(i+1)*self._entrylen] = struct.pack(self.format, *value[j])
		else:
			self._mmap[i*self._entrylen:(i+1)*self._entrylen] = struct.pack(self.format, *value)

	def __len__(self):
		return len(self._mmap) // self._entrylen

	def append(self, *args):
		i = len(self)
		self._mmap.resize(len(self._mmap) + self._entrylen)
		self[i] = args

	def close(self):
		if self._mmap is not None:
			self._mmap.flush()
			self._mmap.close()
			self._mmap = None

class SeriesJson:
	def __init__(self, filename):
		self.filename = filename
		self._data = []
		self.refresh()

	def refresh(self):
		with open(self.filename, 'r') as f:
			self._data = json.load(f)

	def close(self):
		with open(self.filename, 'w') as f:
			self._data = json.dump(self._data, f)

	def append(self, *args):
		self._data.append(args)

	def __len__(self):
		return len(self._data)

	def __setitem__(self, i, value):
		self._data[i] = value

	def __getitem__(self, i):
		return self._data[i]