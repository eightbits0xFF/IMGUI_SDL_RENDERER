// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <imgui.h>
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

int imgui_width = 500;
int imgui_height = 500;




int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Home", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, imgui_width, imgui_height, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);


	SDL_RenderSetLogicalSize(renderer, imgui_width, imgui_height);

	SDL_Surface* bitmap_surface = SDL_CreateRGBSurface(0, imgui_width, imgui_height, 32,
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);


	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);


	SDL_Event event{};
    
    std::string text{"Ok Good"};
    
    while (true)
    {


        if (SDL_PollEvent(&event) == 1) {
            switch (event.type)
            {
            case SDL_QUIT:
                goto QUIT;
            default:
                break;
            }
        }
        ImGui_ImplSDL2_ProcessEvent(&event);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(imgui_width/2, imgui_height/2));
        ImGui::Begin("ImGui");
        if (ImGui::Button(text.c_str()))
        {
            text.append(" YES");
        }
        ImGui::Text("Press 'G' to show or hide this GUI-Window");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
            ImGui::GetIO().Framerate);
        ImGui::Separator();
        ImGui::Text("Scene:");

        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 100, 0, 255));
        if (ImGui::Button("Apply"))
        {

        }
        ImGui::PopStyleColor();
        ImGui::Separator();
        ImGui::End();
        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);


        SDL_Texture* bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmap_surface);
        SDL_RenderCopy(renderer, bitmapTex, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(bitmapTex);

    }
	
QUIT:
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
