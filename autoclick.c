#include<windows.h>
#include<stdio.h>
#include<cpctu_other_funcs.h>
void autoclick(cpctu_arg_type vp);
volatile int delay = 1000;
volatile char left = 'O';
volatile char right = 'P';
int main(int argl, char *argv[])
{
	char cmd[256];
	PINPUT input=(PINPUT)malloc(4*sizeof(*input));
	input->type=INPUT_MOUSE;
	input->mi.dx=0, input->mi.dy=0;
	input->mi.dwFlags=MOUSEEVENTF_RIGHTDOWN;
	input->mi.mouseData=0;
	input->mi.time=0;
	input[1].type=INPUT_MOUSE;
	input[1].mi.dx=0, input->mi.dy=0;
	input[1].mi.dwFlags=MOUSEEVENTF_RIGHTUP;
	input[1].mi.mouseData=0;
	input[1].mi.time=0;

	input[2] = input[0];
	input[3] = input[1];
	input[2].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	input[3].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	cpctu_create_thread(autoclick, input);

	do
	{
		scanf("%s", cmd);
		if(strcmp(cmd, "delay") == 0)
			scanf("%d", &delay);
		else if(strcmp(cmd, "left") == 0)
			scanf(" %c", &left);
		else if(strcmp(cmd, "right") == 0)
			scanf(" %c", &right);
	}
	while(strcmp(cmd, "quit"));

	free(input);
	return 0;
}
void autoclick(cpctu_arg_type vp)
{
	puts("Delay is set to one second by default, left mouse button is O and right mouse button is P.");
	puts("Type command delay to change delay, left to change key for left mouse button, right to change key for right mouse button, and type quit to quit.");
	fflush(stdout);
	LPINPUT input=(LPINPUT)vp;
	for(;;)
	{
		if(GetKeyState(right) >> 15)
		{
			SendInput(2,input,sizeof(*input));
			if(delay)
				cpctu_sleep_thread(delay);
		}
		else if(GetKeyState(left) >> 15)
		{
			SendInput(2,input+2,sizeof(*input));
			if(delay)
				cpctu_sleep_thread(delay);
		}
	}
}
