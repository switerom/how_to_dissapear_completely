uniform sampler2D texture; // the original image
uniform sampler2D overlay; // the overlay image

void main()
{
    vec4 baseColor = texture2D(texture, gl_TexCoord[0].xy);
    vec4 overlayColor = texture2D(overlay, gl_TexCoord[0].xy);

    float alpha = baseColor.a;
    vec3 base = baseColor.rgb;
    vec3 over = overlayColor.rgb;

    // apply soft light blending
    vec3 result;
    for(int i = 0; i < 3; i++)
    {
        if (over[i] <= 0.5)
            result[i] = 2.0 * base[i] * over[i] + base[i] * base[i] * (1.0 - 2.0 * over[i]);
        else
            result[i] = 2.0 * base[i] * (1.0 - over[i]) + sqrt(base[i]) * (2.0 * over[i] - 1.0);
    }

    gl_FragColor = vec4(result, alpha);
}
