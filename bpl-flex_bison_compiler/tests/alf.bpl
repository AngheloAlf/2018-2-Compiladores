string hvb[43];
int i;
int count;
int n;

void print(int h){
	write(hvb[h]);
	writeln();
}

void case(int v){
	if(count < 0){
		print(i);
		i = i + 1;
	}
	if(v==count){
		print(i);
		i = i + 1;
		count = count - 1;
	}
}

void ddevice(void){
	n = (count + 7) / 8;
	n = n + 1;
	count = count % 8;
	while (n = n - 1){
		case(0);
		case(7);
		case(6);
		case(5);
		case(4);
		case(3);
		case(2);
		case(1);
	}
}

void main(void) {
	hvb[36] = "               \\    \\,,,,,,,,,,,,,,,,,,,,,,,,,,,/             ";
    hvb[ 9] = " |,,,|    |,,,,,,,,________/                 \\,,,,,\\          ";
    hvb[34] = "            \\       /,,,,,,,,,,,,,,,,,,,,,,,,,,,\\|            ";
    hvb[13] = " |,,,|      |/                                    \\,,,|       ";
    hvb[ 2] = "         /,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\\                    ";
    hvb[38] = "                   \\  \\,,,,,,,,,,,,,,,,,,,,,,,,/              ";
    hvb[32] = "         \\            /,,,,,,,,<=======>,,,,,,\\   |           ";
    hvb[ 1] = "           /,,,,,,,,,,,,,,,,,,,,,,,,,,,\\                      ";
    hvb[39] = "                     \\ \\,,,,,,,,,,,,,,,,,,,,,,|               ";
    hvb[25] = "   | |                       /        \\               |       ";
    hvb[33] = "           \\         /,,,,,,,,,,,,,,,,,,,,,,,,,\\  /           ";
    hvb[29] = "        \\                /|||||||||||||||||\\        |         ";
    hvb[11] = " |,,,|     |,,,,/                              \\,,,,,\\        ";
    hvb[28] = "       |                  /|||||||||||||||\\         |         ";
    hvb[35] = "             \\     |,,,,,,,,,,,,,,,,,,,,,,,,,,,,/             ";
    hvb[17] = " |--____          /         \\     /         \\         |       ";
    hvb[30] = "        |               /|||||||||||||||||||\\       /         ";
    hvb[22] = " |   |           \\           /|    \\         /        |       ";
    hvb[19] = " |   |        --_|     ___   |---|    ___    |_--     |       ";
    hvb[27] = "     \\                     /|\\_________/|\\          |         ";
    hvb[41] = "                         \\__________________/                 ";
    hvb[15] = " |/                                                  \\|       ";
    hvb[40] = "                       \\\\,,,,,,,,,,,,,,,,,,,,/                ";
    hvb[10] = " |,,,|     |,,,,,,/                           \\,,,,,\\         ";
    hvb[ 7] = "   /,,,,,,,,,,,,,,,,,,,,,,,,,,,/           \\,,,,\\             ";
    hvb[31] = "        |              /|||||||||||||||||||||\\     /          ";
    hvb[20] = " |   |           |     (_)   |   \\    (_)    |        |       ";
    hvb[23] = " |   |            \\_________/ |     \\_______/         |       ";
    hvb[ 8] = "  /,,,/  \\,,,,,,,,,,,,,,,,,,,/              \\,,,,,\\           ";
    hvb[37] = "                 \\   \\,,,,,,,,,,,,,,,,,,,,,,,,,|              ";
    hvb[ 6] = "    /,,,,,,,,,,,,,,,,,,,,,,,,,,,,/       \\,,,,,\\              ";
    hvb[ 4] = "      /,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\\                 ";
    hvb[ 0] = "            ___________________________                       ";
    hvb[14] = " |,,/                                               \\,|       ";
    hvb[16] = " |                 IIIIIIIII       IIIIIIIII          |       ";
    hvb[21] = " |   |           |           |    \\          |        |       ";
    hvb[24] = "  |  |                        /      \\                |       ";
    hvb[ 5] = "     /,,,,,,,,,,,,,,,,,,,,,,,,,,,,______,,,,,,\\               ";
    hvb[18] = " |   \\  ----__   /           |   |           |   __---|       ";
    hvb[42] = "";
    hvb[12] = " |,,,|     |,,/                                 \\,,,,,|       ";
    hvb[26] = "    |                        |         \\             /        ";
    hvb[ 3] = "       /,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\\                  ";

	count = 43;
	i = 0;
	ddevice();
}