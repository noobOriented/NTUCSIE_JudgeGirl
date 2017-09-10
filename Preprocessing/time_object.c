#ifndef MWTIME
#define MWTIME
 
typedef struct Time {
    int hour;
    int minute;
    int second;
} Time;
 
void initTime(Time *time) {
	time->hour = 0;
	time->minute = 0;
	time->second = 0;
}

void setTime(Time *time, int hour, int minute, int second) {
	time->hour = hour;
	time->minute = minute;
	time->second = second;
}

void addTime(Time *time, int hour, int minute, int second) {
	time->hour += hour;
	time->minute += minute;
	time->second += second;
	if(time->second >= 60){
		time->minute += time->second / 60;
		time->second %= 60;
	}
	if(time->minute >= 60){
		time->hour += time->minute / 60;
		time->minute %= 60;
	}
	time->hour %= 24;
}

void printTime(Time *time) {
	#ifdef H24
		if(time->hour < 10)
			printf("0%d", time->hour);
		else
			printf("%d", time->hour);
	#else
		int hour = (time->hour - 1) % 12 + 1;
		if(hour < 10)
			printf("0%d", hour);
		else
			printf("%d", hour);
		if(time->hour >= 12)
			printf("pm");
		else
			printf("am");
	#endif
	printf(":");
	if(time->minute < 10)
		printf("0%d", time->minute);
	else
		printf("%d", time->minute);
	printf(":");
	if(time->second < 10)
		printf("0%d", time->second);
	else
		printf("%d", time->second);
	printf("\n");
}
#endif