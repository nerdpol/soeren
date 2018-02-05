/*
 * Relgerfukntion für Flightcontrol
*/

typedef struct {
  int16_t w;
  int16_t x;
  uint8_t Kp;
  uint8_t Ki;
  uint8_t Kd;
  int16_t esum;
  int16_t ealt;

} regler_param_t;

int16_t regler_fnc(regler_param_t* data,long Ta)    // Ta sind Millisekunden
{
  int32_t e = data->w -data->x;
  data->esum=data->esum+e;
  int32_t y=data->Kp*e/100 + data->Ki*Ta*data->esum/100 + data->Kd*(e-data->ealt)/Ta/100;
  data->ealt=e;
  return y;
}


/*
 * regler_param_t params;
 * ...
 * tmp = regler_fnc(&params);
 */
