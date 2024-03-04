#undef _UNICODE
#undef UNICODE
#include <iostream>
#include <GLExtension.h>

#include <windows.h>

#include <GLWindow.h>



int main(int args, char* argv[]){
	DWORD flag = CCW | LeftHand;
	GLWindow* window = GLCreateWindow(700, 600, "Application", flag);

	//ShowWindow(hwnd, TRUE);
	printf("cmd line :  %s\n", argv[0]);
	uint32_t frame = 0;
	while (GLBeginFrame(window)){
		glClearColor(0.3f,0.3f,0.3f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//printf("redering %d\n", frame);
		frame++;
		GLSwapBuffers(window);
	}
	
	
	
    return 0;
};

