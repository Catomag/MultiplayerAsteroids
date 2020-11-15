#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>

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

int socket_fd;
struct sockaddr_in server_address;
struct hostent* server;

void connect_to_server(const char* address) {
	int socket_fd;
	struct sockaddr_in server_address;
	struct hostent* server;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	// finds host data on machine (transforms a google.com to its actual ip address)
	server = gethostbyname(address);

	bzero(&server_address, sizeof(server_address));

	server_address.sin_family = AF_INET;
	// copies the first address listed to the server address in thing
	bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
	server_address.sin_port = htons(PORT);

	if(connect(socket_fd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
		perror("could not connect to server");
		exit(1);
	}

	printf("Nothing went wrong, client is connected!");

	char message[] = "Hello from client\0";
	send(socket_fd, message, strlen(message) * sizeof(char), 0);

	char buff[255];
	read(socket_fd, buff, 255);

	printf("%s\n", buff);
}

int main() {
	connect_to_server("127.0.0.1");

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
