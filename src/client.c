#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <raylib.h>
#include <raymath.h>

#include "../include/spaceship.h"

#define PORT 8080

#define SPACESHIP_LENGTH 30
#define SPACESHIP_SPAN 10 

void DrawShip(Vector2 pos, float rot, Color col) {
	Vector2 tip =   Vector2Add(pos, Vector2Rotate( (Vector2) { 0, SPACESHIP_LENGTH/2 }, rot));
	Vector2 left =  Vector2Add(pos, Vector2Rotate( (Vector2) { SPACESHIP_SPAN, -SPACESHIP_LENGTH/2 }, rot));
	Vector2 right = Vector2Add(pos, Vector2Rotate( (Vector2) { -SPACESHIP_SPAN, -SPACESHIP_LENGTH/2 }, rot));

	DrawTriangleLines(left, right, tip, col);
}

float rotation_speed = 250.f;
float acceleration_rate = 10.2f;

int main() {
	
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	struct hostent* server;



	InitWindow(800, 800, "testapp");
	
	Ship ship;
	ship.pos = (Vector2) { 400, 400 };
	ship.vel = (Vector2) { 0, 0 };
	ship.rot = 180;


	while(!WindowShouldClose()) {
		ClearBackground(BLACK);

		float delta = GetFrameTime();
		Vector2 dir;

		dir.x = -sin(ship.rot * DEG2RAD);
		dir.y = cos(ship.rot * DEG2RAD);

		ship.vel = Vector2Add(ship.vel, Vector2Scale(dir, delta * acceleration_rate * IsKeyDown(KEY_SPACE)));

		ship.rot += IsKeyDown(KEY_D) * rotation_speed * delta;
		ship.rot -= IsKeyDown(KEY_A) * rotation_speed * delta;

		ship.pos = Vector2Add(ship.pos, Vector2Scale(ship.vel, delta * 10));

		if(ship.pos.x > 800)
			ship.pos.x = 0;
		else if(ship.pos.x < 0)
			ship.pos.x = 800;

		if(ship.pos.y > 800)
			ship.pos.y = 0;
		else if(ship.pos.y < 0)
			ship.pos.y = 800;

		BeginDrawing();
			DrawShip(ship.pos, ship.rot, WHITE);
		EndDrawing();
	}

	return EXIT_SUCCESS;
}
