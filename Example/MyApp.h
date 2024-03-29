#pragma once
#include <iostream>
#include "../MinUI/App.h"
#include "Surface.h"

#include <cstdlib>


class MyApp : public MinUI::App
{
  private:

	const static int IMG_SIZE = 280;

	bool m_first_iteration;

	Surface m_surface;

	float m_alpha, m_beta, m_gamma;

	float m_sigma_a, m_sigma_b;

	MinUI::Color m_color;

  public:

	MyApp() 
	: m_surface(IMG_SIZE)
	{}

	void init()
	{
		setWindowSize(22, 13);

		// Color
		canvas("root").addCanvas("color", { 0, 0}, {9.5, 1}, "");

		canvas("color").addCheckBox("r", "Red",   {0, 0});
		canvas("color").addCheckBox("g", "Green", {3, 0});
		canvas("color").addCheckBox("b", "Blue",  {6, 0});

		// Image
		canvas("root").addImage("img", {0, 2.5}, {IMG_SIZE, IMG_SIZE}, m_surface.RGBData());

		// Rotation
		canvas("root").addCanvas("rotation", {10.5, 0}, {10.5, 3}, "Euler Angles");

		canvas("rotation").addLabel("alpha", "Alpha : ", {0, 0});
		canvas("rotation").addLabel("beta" , "Beta  : ", {0, 1});
		canvas("rotation").addLabel("gamma", "Gamma : ", {0, 2});

		canvas("rotation").addSlider("alpha", {3, 0}, 3, {-M_PI, M_PI});
		canvas("rotation").addSlider("beta",  {3, 1}, 3, {-M_PI, M_PI});
		canvas("rotation").addSlider("gamma", {3, 2}, 3, {-M_PI, M_PI});

		canvas("rotation").addEntry("alpha", {7, 0}, 2, 1);
		canvas("rotation").addEntry("beta",  {7, 1}, 2, 1);
		canvas("rotation").addEntry("gamma", {7, 2}, 2, 1);

		// Sigmas
		canvas("root").addCanvas("sigma", {10.5, 5.5}, {10.5, 2}, "Standard Deviations");

		canvas("sigma").addLabel("sigma_a", "Sigma A :", {0, 0});
		canvas("sigma").addLabel("sigma_b", "Sigma B :", {0, 1});

		canvas("sigma").addSlider("sigma_a", {3, 0}, 3, {0.2, 1.5});
		canvas("sigma").addSlider("sigma_b", {3, 1}, 3, {0.1, .75});

		canvas("sigma").addEntry("sigma_a", {7, 0}, 2, 1);
		canvas("sigma").addEntry("sigma_b", {7, 1}, 2, 1);

		// Buttons
		canvas("root").addButton("reset", "RESET", {10.5, 10}, {5, 2});
		canvas("root").addButton("quit",  "QUIT",  {16,   10}, {5, 2});

		// Misc
		m_first_iteration = true;
	}

	void update()
	{
		// Init ////////////////////////////////////////////

		if (button("reset").isClicked() || m_first_iteration)
		{
			m_alpha = 0;
			m_beta  = 1;
			m_gamma = 0.5;
			m_sigma_a = 0.5;
			m_sigma_b = 0.25;

			entry("alpha").value() = m_alpha;
			entry("beta" ).value() = m_beta;
			entry("gamma").value() = m_gamma;
			entry("sigma_a").value() = m_sigma_a;
			entry("sigma_b").value() = m_sigma_b;

			slider("alpha").value() = m_alpha;
			slider("beta" ).value() = m_beta;
			slider("gamma").value() = m_gamma;
			slider("sigma_a").value() = m_sigma_a;
			slider("sigma_b").value() = m_sigma_b;

			checkbox("r").value() = 1;
			checkbox("g").value() = 0;
			checkbox("b").value() = 0;

			m_first_iteration = false;
		}

		// Get and Set values //////////////////////////////

		// Sliders

		if (slider("alpha").isGrabbed()) {
			m_alpha = slider("alpha").value();
			entry("alpha").value() = m_alpha;
		}

		if (slider("beta").isGrabbed()) {
			m_beta = slider("beta").value();
			entry("beta").value() = m_beta;
		}

		if (slider("gamma").isGrabbed()) {
			m_gamma = slider("gamma").value();
			entry("gamma").value() = m_gamma;
		}

		if (slider("sigma_a").isGrabbed()) {
			m_sigma_a = slider("sigma_a").value();
			entry("sigma_a").value() = m_sigma_a;
		}

		if (slider("sigma_b").isGrabbed()) {
			m_sigma_b = slider("sigma_b").value();
			entry("sigma_b").value() = m_sigma_b;
		}

		// Entries

		if (entry("alpha").newEntry()) {
			m_alpha = entry("alpha").value();
			slider("alpha").value() = m_alpha; 
		}

		if (entry("beta").newEntry()) {
			m_beta = entry("beta").value();
			slider("beta").value() = m_beta; 
		}

		if (entry("gamma").newEntry()) {
			m_gamma = entry("gamma").value();
			slider("gamma").value() = m_gamma; 
		}

		if (entry("sigma_a").newEntry()) {
			m_sigma_a = entry("sigma_a").value();
			slider("sigma_a").value() = m_sigma_a; 
		}

		if (entry("sigma_b").newEntry()) {
			m_sigma_b = entry("sigma_b").value();
			slider("sigma_b").value() = m_sigma_b; 
		}

		// CheckBoxes

		if (checkbox("r").isClicked()) {
			if (checkbox("r").value()) {
				checkbox("g").value() = 0;
				checkbox("b").value() = 0;
			}
		}

		if (checkbox("g").isClicked()) {
			if (checkbox("g").value()) {
				checkbox("r").value() = 0;
				checkbox("b").value() = 0;
			}
		}

		if (checkbox("b").isClicked()) {
			if (checkbox("b").value()) {
				checkbox("r").value() = 0;
				checkbox("g").value() = 0;
			}
		}

		m_color.r = 255 * checkbox("r").value();
		m_color.g = 255 * checkbox("g").value();
		m_color.b = 255 * checkbox("b").value();  

		// Configure and render the Surface ////////////////

		m_surface.setRotX(m_alpha);
		m_surface.setRotY(m_beta);
		m_surface.setRotZ(m_gamma);

		m_surface.setSigmaA(m_sigma_a);
		m_surface.setSigmaB(m_sigma_b);

		m_surface.render(m_color);

		image("img").setData(m_surface.RGBData());

		// Close ///////////////////////////////////////////

		if (button("quit").isClicked())
			close();
	}

};

