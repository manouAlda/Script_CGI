#ifndef FUNCTION_H
#define FUNCTION_H

#define eps pow(10,-4)

void affiche_html ();
void titre_tab1();
void titre_tab2();

float function (float x);
float derivee(float x);
float* dichotomie (float a, float b);
float* newton_tangente (float a, float b);
float equation__droite ( float a, float b );
float* descarte_secante (float a, float b);
float* integral_rectangle (float a, float b);
float* integral_trapeze(float a, float b);

#endif
