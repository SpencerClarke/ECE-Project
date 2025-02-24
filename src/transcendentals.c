/* Computes f^i */
float powfi(float f, int i)
{
	int j;
	int negative = 0;
	float out = 1.0;

	if(i < 0)
	{
		negative = 1;
		i = -i;
	}

	for(j = 0; j < i; j++)
	{
		out *= f;
	}

	if(negative)
	{
		return 1.0/out;
	}
	else
	{
		return out;
	}
}

float absf(float f)
{
	if(f < 0)
		f = -f;
	return f;
}

/* Approximates ln(f) where f is close to 1 using Taylor Series */
float lnf_near_1(float f)
{
        float out;
        int negative = 0;
	/* ln_LUT[] = {ln(1.0), ln(1.1), ln(1.2) ... ln(2.0)} */
	float ln_LUT[] = {0.0, 0.09531017980432493, 0.1823215567939546, 0.26236426446749106, 0.3364722366212129, 0.4054651081081644, 0.47000362924573563, 0.5306282510621704, 0.5877866649021191, 0.6418538861723947, 0.6931471805599453};
	float min_diff = 100.0;
	float expansion_point = 1.0;
	float expansion_point_value = 0.0;
	float divisor;
	int i;
	for(i = 0; i < 10; i++)
	{
		if(min_diff > absf(f - (1 + i/10.0)))
		{
			min_diff = absf(f - (1 + i/10.0));
			expansion_point = 1 + 0.1 * i;
			expansion_point_value = ln_LUT[i];
		}
	}
	
	out = expansion_point_value;
	divisor = expansion_point;
	for(i = 1; i < 30; i++)
	{
		if(negative)
		{
			out -= powfi(f-expansion_point, i) / i / divisor;
			negative = 0;
		}
		else
		{
			out += powfi(f-expansion_point, i) / i / divisor;
			negative = 1;
		}
		divisor *= expansion_point;
	}

	return out;
}

/* Computes ln(f) */
float lnf(float f)
{
        float out;
        unsigned int exponent = ((*((unsigned int *)&f) & 0x7f800000) >> 23) - 127;
        unsigned int mantissa = *((unsigned int *)&f) & 0x7fffff;

        /* Now we'll get the numerical value of the mantissa 1.XXXXX... */
        float fraction;

        /* Set the exponent to 1 (127 or 0x7f after applying bias) */
        *((unsigned int *)&fraction) = (0x7f << 23);

        /* Insert the mantissa */
        *((unsigned int *)&fraction) |= mantissa;

	/* f = fraction * 2^exponent */
        /* ln(f) = ln(fraction * 2^exponent) */
        /* ln(f) = ln(fraction) + ln(2^exponent) */
        /* ln(f) = ln(fraction) + exponent * ln(2) */
        /* ... and fraction is close to 1 */
        out = lnf_near_1(fraction) + exponent * 0.6931471806;

        return out;
}
/* computes f1^f2 where f2 is close to 0 */
float powff_near_0(float f1, float f2)
{
	float out = 1.0;
	float ln_f1 = lnf(f1);
	float multiplier = 1.0;
	float factorial_divisor = 1;
	for(int i = 1; i < 20; i++)
	{
		multiplier *= ln_f1;
		factorial_divisor *= i;
		out += powfi(f2, i) * multiplier / factorial_divisor;
	}
	
	return out;
}
/* Computes f1^f2 */
float powff(float f1, float f2)
{
	int whole_component = (int)f2;
	float decimal_component = f2 - whole_component;

	return powfi(f1, whole_component) * powff_near_0(f1, decimal_component);
}
