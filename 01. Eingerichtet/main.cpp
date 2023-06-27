#include<SFML/Graphics.hpp>
#include<string>
using namespace sf; // statt std, hat zur Folge, dass bei String etc. std:: vor gesetzt werden muss

int main() {
	int mx = 0;    // Flugrichtung x-Achse 
	int speed = 1; // speed vom Laser

	// Spielefenster erstellen
	RenderWindow window(VideoMode(800, 200), "Laser ");   // Fenstergröße 300x breit x 500y hoch Pixel
	window.setFramerateLimit(60);                       // Bilder pro Sekunde

	// Schriftart für die Punktzahl festlegen
	Font font;
	font.loadFromFile("fonts/arial.ttf"); // muss in aktuellen Projektordner liegen

	// Label erstellen 
	Text text("", font);
	
	// Erstellt ein Rechteck, um den Spieler darzustellen
	RectangleShape laser(Vector2f(40, 1)); // (x, y) 40 breit, 10 hoch
	laser.setFillColor(Color::Red);
	laser.setPosition(0, 100);			

	// Debug >> Positionen auslesen
	Text position("", font);
	position.setCharacterSize(15);

	// 2. Game Loop >> sich wiederholender Spielablauf
	while (window.isOpen()) {     // Game wird beendet, wenn das Fenster geschlossen wird 

		Vector2f laserPos = laser.getPosition(); // laser-Position (x,y)

		// Debug Ausgabe
		position.setPosition(10, 150); // x, y  Pixel nach recht, Pixle nach unten
		position.setString(
			"laser: X " + std::to_string((int)laserPos.x) + " Y " + std::to_string((int)laserPos.y) + '\n' +
			"Speed: X " + std::to_string(mx) + " Y " + std::to_string(0) + " drücke links / rechts auf der Tastatur!"); // Debug-Ausgabe


		laser.move(mx, 0); //Ball Bewegung >> Verschiebt das Objekt um einen bestimmten Offset.

		// laser-Bedienung über die Tastatur
		if (Keyboard::isKeyPressed(Keyboard::Left))
				mx = --speed;	
		if (Keyboard::isKeyPressed(Keyboard::Right))
				mx = ++speed;

		// Bildbegrenzung >> nur nach rechts!
		if (laserPos.x >= 800) 
			laser.setPosition(0, 100);

		// Überprüft, ob das Fenster geschlossen wird
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

		// aktualisiert das Bild
		window.clear();
		window.draw(laser);
		window.draw(text);
		window.draw(position);
		window.display();
	}
	return 0;
}