[?1049h[?1h=[1;54r[?12;25h[?12l[?25h[27m[23m[m[H[2J[?25l[54;1H"cat" [New File][2;1H[94m~                                                                                                                                                             [3;1H~                                                                                                                                                             [4;1H~                                                                                                                                                             [5;1H~                                                                                                                                                             [6;1H~                                                                                                                                                             [7;1H~                                                                                                                                                             [8;1H~                                                                                                                                                             [9;1H~                                                                                                                                                             [10;1H~                                                                                                                                                             [11;1H~                                                                                                                                                             [12;1H~                                                                                                                                                             [13;1H~                                                                                                                                                             [14;1H~                                                                                                                                                             [15;1H~                                                                                                                                                             [16;1H~                                                                                                                                                             [17;1H~                                                                                                                                                             [18;1H~                                                                                                                                                             [19;1H~                                                                                                                                                             [20;1H~                                                                                                                                                             [21;1H~                                                                                                                                                             [22;1H~                                                                                                                                                             [23;1H~                                                                                                                                                             [24;1H~                                                                                                                                                             [25;1H~                                                                                                                                                             [26;1H~                                                                                                                                                             [27;1H~                                                                                                                                                             [28;1H~                                                                                                                                                             [29;1H~                                                                                                                                                             [30;1H~                                                                                                                                                             [31;1H~                                                                                                                                                             [32;1H~                                                                                                                                                             [33;1H~                                                                                                                                                             [34;1H~                                                                                                                                                             [35;1H~                                                                                                                                                             [36;1H~                                                                                                                                                             [37;1H~                                                                                                                                                             [38;1H~                                                                                                                                                             [39;1H~                                                                                                                                                             [40;1H~                                                                                                                                                             [41;1H~                                                                                                                                                             [42;1H~                                                                                                                                                             [43;1H~                                                                                                                                                             [44;1H~                                                                                                                                                             [45;1H~                                                                                                                                                             [46;1H~                                                                                                                                                             [47;1H~                                                                                                                                                             [48;1H~                                                                                                                                                             [49;1H~                                                                                                                                                             [50;1H~                                                                                                                                                             [51;1H~                                                                                                                                                             [52;1H~                                                                                                                                                             [53;1H~                                                                                                                                                             [m[54;141H0,0-1[9CAll[1;1H[?12l[?25h[?25l[54;1H[K[54;1H/*********************************************************************
[97m[41mE61: Nested *[m
[32mPress ENTER or type command to continue[m[1;1H[2L[2;1H[94m~                                                                                                                                                             [m[54;1H[K[54;141H0,0-1[9CAll[1;1H[?12l[?25h[?25l[54;1H[97m[41mE348: No string under cursor[m[54;141H[K[54;141H0,0-1[9CAll[1;1H[?12l[?25h[?25l[54;1H/*********************************************************************[54;141H[K[54;1H[97m[41mE871: (NFA regexp) Can't have a multi follow a multi ![m[54;55H[K[54;1H
[97m[41mE61: Nested *[m
[32mPress ENTER or type command to continue[m[1;1H[2L[2;1H[94m~                                                                                                                                                             [m[54;1H[K[54;141H0,0-1[9CAll[1;1H[?12l[?25h[?25l[54;1H[1m-- INSERT --[m[54;141H[K[54;141H0,1[11CAll[1;25Hsha256_transform(ctx, ctx->data);
                        ctx->bitlen += 512;[2;44H[K[3;1H                        ctx->datalen = 0;[3;42H[K[4;1H                }[4;18H[K[5;1H        }[5;10H[K[6;1H}[6;2H[K[7;1H[K[8;1Hvoid sha256_final(SHA256_CTX *ctx, BYTE hash[])[8;48H[K[9;1H{[9;2H[K[10;1H        WORD i;[10;16H[K[11;1H[K[12;1H        i = ctx->datalen;[12;26H[K[13;1H[K[14;1H        // Pad whatever data is left in the buffer.[14;52H[K[15;1H        if (ctx->datalen < 56) {[15;33H[K[16;1H                ctx->data[i++] = 0x80;[16;39H[K[17;1H                while (i < 56)[17;31H[K[18;1H                        ctx->data[i++] = 0x00;[18;47H[K[19;1H        }[19;10H[K[20;1H        else {[20;15H[K[21;1H                ctx->data[i++] = 0x80;[21;39H[K[22;1H                while (i < 64)[22;31H[K[23;1H                        ctx->data[i++] = 0x00;[23;47H[K[24;1H                sha256_transform(ctx, ctx->data);[24;50H[K[25;1H                memset(ctx->data, 0, 56);[25;42H[K[26;1H        }[26;10H[K[27;1H[K[28;1H        // Append to the padding the total message's length in bits and transform.[28;83H[K[29;1H        ctx->bitlen += ctx->datalen * 8;[29;41H[K[30;1H        ctx->data[63] = ctx->bitlen;[30;37H[K[31;1H        ctx->data[62] = ctx->bitlen >> 8;[31;42H[K[32;1H        ctx->data[61] = ctx->bitlen >> 16;[32;43H[K[33;1H        ctx->data[60] = ctx->bitlen >> 24;[33;43H[K[34;1H        ctx->data[59] = ctx->bitlen >> 32;[34;43H[K[35;1H        ctx->data[58] = ctx->bitlen >> 40;[35;43H[K[36;1H        ctx->data[57] = ctx->bitlen >> 48;[36;43H[K[37;1H        ctx->data[56] = ctx->bitlen >> 56;[37;43H[K[38;1H        sha256_transform(ctx, ctx->data);[38;42H[K[39;1H[K[40;1H        // Since this implementation uses little endian byte ordering and SHA uses big endian,[40;95H[K[41;1H        // reverse all the bytes when copying the final state to the output hash.[41;82H[K[42;1H        for (i = 0; i < 4; ++i) {[42;34H[K[43;1H                hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;[43;77H[K[44;1H                hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;[44;77H[K[45;1H                hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;[45;77H[K[46;1H                hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;[46;77H[K[47;1H                hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;[47;77H[K[48;1H                hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;[48;77H[K[49;1H                hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;[49;77H[K[50;1H                hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;[50;77H[K[51;1H        }[51;10H[K[52;1H}[52;2H[K[53;1H[K[54;141H158,1[9CBot[53;1H[?12l[?25h[?25l[1;53r[53;1H
[1;54r[54;141H[K[54;141H159,1[9CBot[53;1H[?12l[?25h[?25l[54;1H[K[54;141H159,0-1[7CBot[53;1H[?12l[?25h[?25l
Type  :quit<Enter>  to exit Vim[54;141H[K[54;141H159,0-1[7CBot[53;1H[?12l[?25h[?25l[54;141H[K[54;141H159,0-1[7CBot[53;1H[?12l[?25h[?25l[54;141H[K[54;141H159,0-1[7CBot[53;1H[?12l[?25h[?25l[54;141H[K[54;141H159,0-1[7CBot[53;1H[?12l[?25h
[?1l>[?1049lVim: Error reading input, exiting...
Vim: preserving files...
Vim: Finished.
[54;1H