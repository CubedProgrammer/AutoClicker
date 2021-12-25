#include<ctype.h>
#include<process.h>
#include<stdio.h>
#include<windows.h>
unsigned autoclick(void *vp);
volatile int delay = 1000;
volatile char left = 'O';
volatile char right = 'P';
volatile char toggle = 0;
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
	_beginthreadex(NULL, 0, autoclick, input, 0, NULL);

	do
	{
		scanf("%s", cmd);
		if(strcmp(cmd, "delay") == 0)
			scanf("%d", &delay);
		else if(strcmp(cmd, "left") == 0)
			scanf(" %c", &left);
		else if(strcmp(cmd, "right") == 0)
			scanf(" %c", &right);
		else if(strcmp(cmd, "toggle") == 0)
			toggle = ~toggle;
		left = toupper(left);
		right = toupper(right);
	}
	while(strcmp(cmd, "quit"));

	free(input);
	return 0;
}
unsigned autoclick(void *vp)
{
	puts("Delay is set to one second by default, left mouse button is O and right mouse button is P.");
	puts("Type command delay to change delay, left to change key for left mouse button, right to change key for right mouse button, and type quit to quit.");
	fflush(stdout);
	LPINPUT input=(LPINPUT)vp;
	char lt = 0, rt = 0;
	char cl = 0, cr = 0;
	char ll = 0, lr = 0;
	for(;;Sleep(delay))
	{
		cl = GetKeyState(left) >> 15;
		cr = GetKeyState(right) >> 15;
		if(toggle)
		{
			if(ll&&!cl)
				lt = !lt;
			if(lr&&!cr)
				rt = !rt;
			ll = cl;
			lr = cr;
		}
		else
		{
			lt = cl;
			rt = cr;
		}
		if(rt)
			SendInput(2,input,sizeof(*input));
		if(lt)
			SendInput(2,input+2,sizeof(*input));
	}
	return 0;
}
