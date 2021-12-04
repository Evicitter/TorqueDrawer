#include <string>
#include <iostream>
#include <fstream>

//SFML
#include <SFML\Graphics.hpp>

//utils
#include "utils\CurveEval.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int wmain()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	//float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };

	bool p_open = true;

	bool bsel_torquedraw = true;
	bool bsel_powerdraw = false;

	//window.setTitle();
	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::SetNextWindowSize(ImVec2(500, 110));
		ImGui::SetNextWindowPos(ImVec2(0,0));
		ImGui::Begin("Options Layer", &p_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar); // begin window

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) { p_open = false; }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Draw Mode"))
			{
				if (ImGui::MenuItem("Draw Torque", nullptr, &bsel_torquedraw))	{ bsel_torquedraw = true;	bsel_powerdraw = false; }
				if (ImGui::MenuItem("Draw Power", nullptr, &bsel_powerdraw))	{ bsel_torquedraw = false;	bsel_powerdraw = true; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End(); // end window

		window.clear();
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}