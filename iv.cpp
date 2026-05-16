#include<iostream>
#include<SDL3/SDL.h>
#include<fstream>

int main(int argc,char* argv[]){
	//check if the file is in argument or not
	if (argc < 2){
		printf("no file is there\n");
		return 0;
	}
	//opening the file
	std::ifstream imgppm;
	imgppm.open(argv[1],std::ios::binary);
	
	//reading 1st line
	std::string head;
	imgppm >> head;

	int width,height;
	imgppm >> width >> height;

	int maxval;
	imgppm >> maxval;
	imgppm.ignore(1);

	SDL_Window* pwindow = SDL_CreateWindow("image viwer",width,height,SDL_WINDOW_RESIZABLE);
	SDL_Surface* psurface = SDL_GetWindowSurface(pwindow);
	Uint8 r,g,b;
	r = g = 0x00;
	b = 0x00;
	const SDL_PixelFormatDetails* fD = SDL_GetPixelFormatDetails(psurface->format);
	SDL_Rect pixel = (SDL_Rect){0,0,1,1};

	for (int y=0; y <height;y++){
		for (int x=0;x<width;x++){
			imgppm.read((char*)&r,1);
			imgppm.read((char*)&g,1);
			imgppm.read((char*)&b,1);
			Uint32 color = SDL_MapRGB(fD,NULL,r,g,b);
			pixel.x = x;
			pixel.y = y;
			SDL_FillSurfaceRect(psurface,&pixel,color);
		}
		SDL_Delay(3);
		SDL_UpdateWindowSurface(pwindow);
	}
	int done = 1;
	SDL_Event event;
	SDL_UpdateWindowSurface(pwindow);
	while(done){
		while(SDL_PollEvent(&event)){
			if (event.type == SDL_EVENT_QUIT){
				done = 0;
			}
		}
	}

}
