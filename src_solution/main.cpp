#include <chrono>
#include <cstdlib>
#include <thread>
#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "constants.h"
#include "bird.h"
#include "track.h"


int main() {
	srand(time(nullptr));
	auto win = std::make_unique<Fl_Double_Window>(screenWidth, screenHeight, "Flappy");
	win->color(FL_WHITE);


	Track* track = new Track(win->w(), win->h());

	win->end();
	win->show();

	auto nextDrawing = std::chrono::steady_clock::now();

	while (win->shown())
	{
		// Sleep until next drawing

		std::this_thread::sleep_until(nextDrawing);
		nextDrawing += std::chrono::microseconds(1'000'000 / frameRate);

		Fl::check(); // Handles input
		Fl::redraw(); // Call draw
	}
}