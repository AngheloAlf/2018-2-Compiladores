string hvb[43];
int i;
int count;
int n;

int print(int h){
	write(hvb[h]);
	writeln();
}

void case(int v){
	if(count<0){
		print(i);
		i=i+1;
	}
	if(v==count){
		print(i);
		i=i+1;
		count=count-1;
	}
}

void ddevice(void){
	n = (count + 7) / 8;
	n = n+1;
	count = count % 8;
	while (n = n-1){
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
	hvb[0] = "            ___________________________                       ";hvb[42] = "";hvb[41] = "                         \\__________________/                 ";hvb[20] = " |   |           |     (_)   |   \\    (_)    |        |       ";hvb[16] = " |                 IIIIIIIII       IIIIIIIII          |       ";hvb[32] = "         \\            /,,,,,,,,<=======>,,,,,,\\   |           ";hvb[13] = " |,,,|      |/                                    \\,,,|       ";hvb[26] = "    |                        |         \\             /        ";hvb[37] = "                 \\   \\,,,,,,,,,,,,,,,,,,,,,,,,,|              ";hvb[5] = "     /,,,,,,,,,,,,,,,,,,,,,,,,,,,,______,,,,,,\\               ";hvb[27] = "     \\                     /|\\_________/|\\          |         ";hvb[36] = "               \\    \\,,,,,,,,,,,,,,,,,,,,,,,,,,,/             ";hvb[24] = "  |  |                        /      \\                |       ";hvb[9] = " |,,,|    |,,,,,,,,________/                 \\,,,,,\\          ";hvb[30] = "        |               /|||||||||||||||||||\\       /         ";hvb[38] = "                   \\  \\,,,,,,,,,,,,,,,,,,,,,,,,/              ";hvb[12] = " |,,,|     |,,/                                 \\,,,,,|       ";hvb[19] = " |   |        --_|     ___   |---|    ___    |_--     |       ";hvb[29] = "        \\                /|||||||||||||||||\\        |         ";hvb[1] = "           /,,,,,,,,,,,,,,,,,,,,,,,,,,,\\                      ";hvb[11] = " |,,,|     |,,,,/                              \\,,,,,\\        ";hvb[22] = " |   |           \\           /|    \\         /        |       ";hvb[34] = "            \\       /,,,,,,,,,,,,,,,,,,,,,,,,,,,\\|            ";hvb[18] = " |   \\  ----__   /           |   |           |   __---|       ";hvb[7] = "   /,,,,,,,,,,,,,,,,,,,,,,,,,,,/           \\,,,,\\             ";hvb[23] = " |   |            \\_________/ |     \\_______/         |       ";hvb[17] = " |--____          /         \\     /         \\         |       ";hvb[2] = "         /,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\\                    ";hvb[31] = "        |              /|||||||||||||||||||||\\     /          ";hvb[8] = "  /,,,/  \\,,,,,,,,,,,,,,,,,,,/              \\,,,,,\\           ";hvb[35] = "             \\     |,,,,,,,,,,,,,,,,,,,,,,,,,,,,/             ";hvb[14] = " |,,/                                               \\,|       ";hvb[39] = "                     \\ \\,,,,,,,,,,,,,,,,,,,,,,|               ";hvb[28] = "       |                  /|||||||||||||||\\         |         ";hvb[4] = "      /,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\\                 ";hvb[33] = "           \\         /,,,,,,,,,,,,,,,,,,,,,,,,,\\  /           ";hvb[21] = " |   |           |           |    \\          |        |       ";hvb[3] = "       /,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\\                  ";hvb[40] = "                       \\\\,,,,,,,,,,,,,,,,,,,,/                ";hvb[15] = " |/                                                  \\|       ";hvb[10] = " |,,,|     |,,,,,,/                           \\,,,,,\\         ";hvb[25] = "   | |                       /        \\               |       ";hvb[6] = "    /,,,,,,,,,,,,,,,,,,,,,,,,,,,,/       \\,,,,,\\              ";
	
	count = 43;
	i=0;
	ddevice();
}