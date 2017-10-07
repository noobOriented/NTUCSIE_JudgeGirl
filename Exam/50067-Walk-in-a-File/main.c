#include <stdio.h>

FILE *f;
char tmp_char;
int i, type, tmp_int, flag = 1;

int main() {
	char file_name[16];
	scanf("%s", file_name);
	f = fopen(file_name, "rb");
	while(fread(&type, 4, 1, f) == 1) {
		switch(type) {
			case 0:
				fread(&tmp_int, 4, 1, f);
				printf("%d", tmp_int);
				break;
			case 1:
				for(i = 0; i < 4; ++i) {
					putchar(fgetc(f));
				}
				break;
			case 2:
				fread(&tmp_int, 4, 1, f);
				while((tmp_char = fgetc(f)) != '\0') {
					putchar(tmp_char);
				}
				break;
			case 3:
				fread(&tmp_int, 4, 1, f);
				fseek(f, tmp_int-8, SEEK_CUR);
				break;
			case 4:
				fread(&tmp_int, 4, 1, f);
				fseek(f, tmp_int, SEEK_SET);
				break;
			case 5:
				fread(&tmp_int, 4, 1, f);
				fseek(f, tmp_int, SEEK_END);
				break;
			default:
				printf("Seek end");
				fclose(f);
				return 0;
		}
	}
	fclose(f);
}