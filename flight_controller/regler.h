/*
 * Relgerfukntion für Flightcontrol
*/

typedef struct {
  uint16_t w;
  uint16_t x;
  uint8_t Kp;
  uint8_t Ki;
  uint8_t Kd;
  uint16_t esum;
  uint16_t ealt;

} regler_param_t;

uint16_t regler_fnc(regler_param_t* data,long Ta)
{
  uint16_t e = data->w -data->x;
  data->esum=data->esum+e;
  uint16_t y=data->Kp*e+data->Ki*Ta*data->esum+data->Kd/Ta*(e-data->ealt);
  data->ealt=e;
  return y;
}


/*
 * regler_param_t params;
 * ...
 * tmp = regler_fnc(&params);
 */
