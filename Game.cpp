#include "Game.h"
#include "Player.h"
#include "Bullet1.h"
#include "Bullet2.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "boss.h"
#include "star.h"
#include "heart.h"
#include <iostream>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <SFML/Audio.hpp>
#include <conio.h>
#include <algorithm>
using namespace std;


Game::Game()
{
	state = END;

	if (!font.loadFromFile("arial.ttf"))
	{
		MessageBox(NULL, "Czcionka nie zostala zaladowana", "ERROR", NULL);
		return;
	}

	state = MENU;
}


Game::~Game()
{
}

void Game::runGame()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;

		case GameState::GAME:
			Play();
			break;

		case GameState::RANKING:
			Ranking();
			break;
		
		case GameState::AUTHOR:
			Author();
			break;
		}
	}
}
void Game::Ranking()
{
	struct gracz
	{
		string nick;
		int score;
	};
	std::vector<gracz> Players;
	ifstream wejscie;
	wejscie.open("RankingNotSorted.txt");
	int j = 0;
	while (!wejscie.eof())
	{
		gracz Element;
		wejscie >> Element.nick;
		wejscie >> Element.score;
		Players.push_back(Element);
		//std::cout << Element.nick << " " << Element.score << std::endl;
		j++;
	}
	//std::cout << j << std::endl;
	std::sort(Players.begin(), Players.end()-1, [](const gracz& lhs, const gracz& rhs)
	{
		return lhs.score > rhs.score;
	});
	/*
	for (int i = 0; i < Players.size(); i++)
	{
		std::cout << Players[i].nick << " " << Players[i].score << std::endl;
	}
	*/
	
	
	
	
	ofstream wynik;
	wynik.open("Ranking.txt");
	for (int i = 0; i < 3; i++)
	{
		wynik << Players[i].nick << " " << Players[i].score << std::endl;
	}
	
	sf::RenderWindow RankingWindow(sf::VideoMode(1280, 720), "Ranking", sf::Style::Close);

	Text Names[3];
	Text Points[3];
	int Scores[3];
	ifstream wejscie2;
	wejscie2.open("Ranking.txt");
	for (int i = 0; i < 3; i++)
	{
		Names[i].setFont(font);
		Names[i].setCharacterSize(55);
		string name;
		wejscie2 >> name;
		Names[i].setString(name);
		Names[i].setPosition(1280 / 2 - Names[i].getGlobalBounds().width / 2-50, 250 + i * 150);
		wejscie2 >> Scores[i];
		Points[i].setFont(font);
		Points[i].setCharacterSize(55);
		Points[i].setString(std::to_string(Scores[i]));
		Points[i].setPosition(1280 / 2 - Points[i].getGlobalBounds().width / 2 + 150, 250 + i * 150);

	}
	Text Back;
	string back = "Back";
	Back.setFont(font);
	Back.setCharacterSize(50);
	Back.setFillColor(sf::Color::White);
	Back.setString(back);
	Back.setPosition(20, 20);

	Texture ranking;
	ranking.loadFromFile("ranking.png");
	Sprite background;
	background.setTexture(ranking);

	Texture TrophyTexture;
	TrophyTexture.loadFromFile("trophy.png");
	Sprite Trophy;
	Trophy.setTexture(TrophyTexture);
	Trophy.setRotation(20);
	Trophy.setScale(1.25f, 1.25f);
	Trophy.setPosition(900, 150);
	while (state == RANKING)
	{
		Vector2f mouse(Mouse::getPosition(RankingWindow));
		Event event;
		while (RankingWindow.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				state = END;
		}

		if (Back.getGlobalBounds().contains(mouse))
			{
				Back.setFillColor(Color::Red);
			}
				
			else Back.setFillColor(Color::White);

			if (Back.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = MENU;
			}

		RankingWindow.clear();
		RankingWindow.draw(background);
		for (int i = 0; i < 3; i++)
		{
			RankingWindow.draw(Names[i]);
		}
		for (int i = 0; i < 3; i++)
		{
			RankingWindow.draw(Points[i]);
		}
		RankingWindow.draw(Back);
		RankingWindow.draw(Trophy);
		RankingWindow.display();
	}
	
	
	
}
void Game::menu()
{
	//Text title("Space Mission", font, 70);
	//title.setStyle(Text::Bold);
	sf::RenderWindow window(sf::VideoMode(1280, 680), "Space Mission - production by Michal Adamski", sf::Style::Close);
	//title.setPosition(sf::Vector2f(1280 / 2 - title.getLocalBounds().width / 2, 20));

	Texture StartTextur;
	StartTextur.loadFromFile("start.png");
	Sprite Start;
	Start.setTexture(StartTextur);

	const int ile = 3;

	Text tekst[ile];

	string str[] = { "Play" , "Ranking" , "Author" };
	for (int i = 0; i < ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(55);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280 / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 150);

	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				state = END;

			else if (tekst[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME;
			}

			else if (tekst[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = RANKING;
			}
			else if (tekst[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = AUTHOR;
			}
		}

		for (int i = 0; i < ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setFillColor(Color::Red);
			else tekst[i].setFillColor(Color::White);

			window.clear();

			window.draw(Start);
			for (int i = 0; i < ile; i++)
				window.draw(tekst[i]);

			window.display();

	}
}

void Game::Author()
{
	sf::RenderWindow AuthorWindow(sf::VideoMode(1280, 720), "Author");

	Texture BackGroundTexture;
	BackGroundTexture.loadFromFile("author.png");
	Sprite BackGround;
	BackGround.setTexture(BackGroundTexture);

	Texture MeTexture;
	MeTexture.loadFromFile("me.png");
	Sprite Me;
	Me.setTexture(MeTexture);
	Me.setScale(0.8f, 0.8f);
	Me.setPosition(340, 220);

	Text Back;
	string back = "Back";
	Back.setFont(font);
	Back.setCharacterSize(50);
	Back.setFillColor(sf::Color::White);
	Back.setString(back);
	Back.setPosition(20, 20);



	while (state == AUTHOR)
	{
		Vector2f mouse(Mouse::getPosition(AuthorWindow));
		Event event;
		while (AuthorWindow.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				state = END;
		}

		if (Back.getGlobalBounds().contains(mouse))
		{
			Back.setFillColor(Color::Red);
		}

		else Back.setFillColor(Color::White);

		if (Back.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			state = MENU;
		}
	
	AuthorWindow.clear();
	AuthorWindow.draw(BackGround);
	AuthorWindow.draw(Back);
	AuthorWindow.draw(Me);
	AuthorWindow.display();
	}
}

void Game::Play()
{
	//srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(800, 850), "Game");
	window.setFramerateLimit(60);


	//Font init
	Font font;
	font.loadFromFile("arial.ttf");
	//end font init

	//Score text init 
	Text Score;
	Score.setFont(font);
	Score.setCharacterSize(40);
	Score.setFillColor(sf::Color::White);
	Score.setPosition(600, 780);
	//end Score text init

	//Hp text Init
	Text HpText;
	HpText.setFont(font);
	HpText.setCharacterSize(40);
	HpText.setFillColor(sf::Color::Red);
	HpText.setPosition(20, 780);
	//end HP text init

	//Player-ship init
	Texture playerTexture;
	playerTexture.loadFromFile("ship.png");
	Player player(&playerTexture);
	// end Player ship init

	//Bullet1 init
	Texture BulletTexture;
	BulletTexture.loadFromFile("missile1.png");
	//end Bullet1 init

	//Bullet2 init
	Texture Bullet2Texture;
	Bullet2Texture.loadFromFile("bullet2.png");
	//end Bullet2 init

	//Bullet 1 Boss init
	Texture BulletBoss1Texture;
	BulletBoss1Texture.loadFromFile("BulletBoss1.png");
	//end Bullet1 Boss init

	//Bullet 2 Boss init
	Texture BulletBoss2Texture;
	BulletBoss2Texture.loadFromFile("BulletBoss1.png");
	//end Bullet 2 Boss init

	//Bullet 3 Boss init
	Texture BulletBoss3Texture;
	BulletBoss3Texture.loadFromFile("BulletBoss2.png");
	//end Bullet3 Boss init

	//Bullet 4 Boss init
	Texture BulletBoss4Texture;
	BulletBoss4Texture.loadFromFile("BulletBoss2.png");
	//end Bullet 4 Boss init


	//star bonus init
	Texture StarTexture;
	StarTexture.loadFromFile("star.png");
	int StarSpawn = 0;
	std::vector<star> stars;
	//star bonus end init

	//heart bonus init
	Texture HeartTexture;
	HeartTexture.loadFromFile("heart.png");
	int HeartSpawn = 0;
	std::vector<heart> hearts;
	//end heart bonus init


	//Enemy1 init
	Texture Enemy1Texture;
	Enemy1Texture.loadFromFile("enemy.png");
	int EnemySpawn1 = 0;
	std::vector<Enemy1> enemies1;
	//end Enemy1 init


	//Enemy2 init
	Texture Enemy2Texture;
	Enemy2Texture.loadFromFile("enemy2.png");
	int EnemySpawn2 = 0;
	std::vector<Enemy2> enemies2;
	//end Enemy2 init

	//Enemy3 init
	Texture Enemy3Texture;
	Enemy3Texture.loadFromFile("enemy3.png");
	int EnemySpawn3 = 0;
	std::vector<Enemy3> enemies3;
	//end Enemy3 init

	//Enemy4 init
	Texture Enemy4Texture;
	Enemy4Texture.loadFromFile("enemy4.png");
	int EnemySpawn4 = 0;
	std::vector<Enemy4> enemies4;
	//end Enemy4 init

	//Enemy5 init
	Texture Enemy5Texture;
	Enemy5Texture.loadFromFile("enemy4.png");
	int EnemySpawn5 = 0;
	std::vector<Enemy5> enemies5;
	//end Enemy5 init

	//Boss init
	Texture BossTexture;
	BossTexture.loadFromFile("boss2.png");
	std::vector<boss> Boss;
	int condition_boos = 0;
	//Boss end init

	//map load
	Sprite map;
	Texture MapTexture;
	MapTexture.loadFromFile("map.png");
	map.setTexture(MapTexture);
	//end map load

	//background for highscore
	Sprite background;
	Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("1.png");
	background.setTexture(BackgroundTexture);

	//end background for highscore
	sf::Music music;
	music.openFromFile("music.ogg");
	music.play();
	string NamePlayer = "";
	
	while (state == GAME)
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				state = END;


			if (player.HP <= 0)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
				{
					NamePlayer = "";
				}


				else if (event.type == sf::Event::TextEntered)
					if (event.text.unicode != ' ')
						if (event.text.unicode > 31 && event.text.unicode < 128)
						{
							NamePlayer += static_cast<char>(event.text.unicode);

						}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && NamePlayer.size() > 0)
				{
					//also add to file
					std::ofstream out;
					out.open("RankingNotSorted.txt", std::ofstream::app);
					out << NamePlayer + " " + std::to_string(player.score) + "\n";
					std::cout << NamePlayer << std::endl;
					window.close();
					state = MENU;

				}
			}
		}

		//condition end player life
		if (player.HP > 0)
		{
			//Player move
			if (sf::Keyboard::isKeyPressed(Keyboard::W))
				player.shape.move(0.f, -8.0f);

			if (sf::Keyboard::isKeyPressed(Keyboard::A))
				player.shape.move(-8.f, 0.0f);

			if (sf::Keyboard::isKeyPressed(Keyboard::S))
				player.shape.move(0.f, 8.0f);

			if (sf::Keyboard::isKeyPressed(Keyboard::D))
				player.shape.move(8.f, 0.0f);

			if (player.shape.getPosition().x <= 0)
				player.shape.setPosition(0.f, player.shape.getPosition().y);

			if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width)
				player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);

			if (player.shape.getPosition().y <= 0)
				player.shape.setPosition(player.shape.getPosition().x, 0.f);

			if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height)
				player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
			// end Player move


			//Helpful while
			if (player.score == 15 || player.score == 16)
			{
				player.score += 2;
				for (size_t i = 0; i < enemies1.size(); i++)
				{
					enemies1.erase(enemies1.begin() + i);
				}
			}

			if (player.score == 30 || player.score == 31)
			{
				player.score += 2;
				for (size_t i = 0; i < enemies2.size(); i++)
				{
					enemies2.erase(enemies2.begin() + i);
				}
			}
			if (player.score == 60 || player.score == 61)
			{
				for (size_t i = 0; i < enemies3.size(); i++)
				{
					enemies3.erase(enemies3.begin() + i);
				}
			}

			if (player.score == 100 || player.score == 101)
			{
				player.score++;
				for (size_t i = 0; i < enemies5.size(); i++)
				{
					enemies5.erase(enemies5.begin() + i);
				}
			}

			//helpful




			//Shooting bullet1
			if (player.shootTimer <= 15)
			{
				player.shootTimer++;
			}
			if (sf::Mouse::isButtonPressed(Mouse::Left) && player.shootTimer >= 15)
			{
				player.bullets1.push_back(Bullet1(&BulletTexture, Vector2f(player.shape.getPosition().x + 25, player.shape.getPosition().y - 10)));
				player.shootTimer = 0;
			}
			for (size_t i = 0; i < player.bullets1.size(); i++)
			{

				player.bullets1[i].shape.move(0.f, -20.f); //Move bullets1

				//Collision bullets1 with screen

				if (player.bullets1[i].shape.getPosition().y <= 0)
				{
					player.bullets1.erase(player.bullets1.begin() + i);
					break;
				}
				// end Collision bullets1 with screen
				if (player.score <= 15)
				{
					//Collision Bullets1 with Enemies1
					for (size_t k = 0; k < enemies1.size(); k++)
					{
						if (player.bullets1[i].shape.getGlobalBounds().intersects(enemies1[k].shape.getGlobalBounds()))
						{
							enemies1.erase(enemies1.begin() + k);
							player.bullets1.erase(player.bullets1.begin() + i);
							player.score++;
							break;
						}
					}
					//end Collision Bullets1 with Enemies1

				}
				//Collision Bullets1 with Enemies2
				if (player.score > 15 && player.score <= 30)
				{

					for (size_t k = 0; k < enemies2.size(); k++)
					{
						if (player.bullets1[i].shape.getGlobalBounds().intersects(enemies2[k].shape.getGlobalBounds()))
						{
							if (enemies2[k].HP <= 1)
							{
								player.score += 1;
								enemies2.erase(enemies2.begin() + k);
							}
							else
								enemies2[k].HP--;


							player.bullets1.erase(player.bullets1.begin() + i);
							break;
						}
					}

				}
				//end Collision Bullets1 with Enemies2

				//Collision Bullets1 with Enemies3
				if (player.score >= 30 && player.score <= 60)
				{

					for (size_t k = 0; k < enemies3.size(); k++)
					{
						if (player.bullets1[i].shape.getGlobalBounds().intersects(enemies3[k].shape.getGlobalBounds()))
						{
							if (enemies3[k].HP <= 1)
							{
								player.score += 1;
								enemies3.erase(enemies3.begin() + k);
							}
							else
								enemies3[k].HP--;


							player.bullets1.erase(player.bullets1.begin() + i);
							break;
						}
					}

				}
				//end Collision Bullets1 with Enemies3

				//Collision Bullets1 with Enemies4

				if (player.score >= 60 && player.score <= 80)
				{
					for (size_t k = 0; k < enemies4.size(); k++)
					{
						if (player.bullets1[i].shape.getGlobalBounds().intersects(enemies4[k].shape.getGlobalBounds()))
						{
							if (enemies4[k].HP <= 1)
							{
								player.score += 1;
								enemies4.erase(enemies4.begin() + k);
							}
							else
								enemies4[k].HP--;


							player.bullets1.erase(player.bullets1.begin() + i);
							break;
						}
					}
				}
				//end Collision Bullets1 with Enemies4

				//Collision Bullets1 with Enemies5

				if (player.score >= 80 && player.score <= 100)
				{
					for (size_t k = 0; k < enemies5.size(); k++)
					{
						if (player.bullets1[i].shape.getGlobalBounds().intersects(enemies5[k].shape.getGlobalBounds()))
						{
							if (enemies5[k].HP <= 1)
							{
								player.score += 1;
								enemies5.erase(enemies5.begin() + k);
							}
							else
								enemies5[k].HP--;


							player.bullets1.erase(player.bullets1.begin() + i);
							break;
						}
					}
				}
				//end Collision Bullets1 with Enemies5

				//Collision Bullets1 with Boss

				if (player.score >= 100)
				{
					for (size_t k = 0; k < Boss.size(); k++)
					{
						if (player.bullets1[i].shape.getGlobalBounds().intersects(Boss[k].shape.getGlobalBounds()))
						{
							if (Boss[k].HP <= 1)
							{
								player.score += 100;
								Boss.erase(Boss.begin());
								player.HP = player.HP - 15;
							}
							else
								Boss[k].HP--;


							player.bullets1.erase(player.bullets1.begin() + i);
							break;
						}

					}
				}
				//end Collision Bullets1 with Boss
			}
			// end Shooting bullet1

			//Shooting Bullet2 Enemy
			if (player.score >= 30 && player.score <= 60)
			{
				for (size_t i = 0; i < enemies3.size(); i++)
				{
					if (enemies3[i].shootTimer2 <= 40)
					{
						enemies3[i].shootTimer2++;
					}
					else
					{
						enemies3[i].bullets2.push_back(Bullet2(&Bullet2Texture, Vector2f(enemies3[i].shape.getPosition().x + 27, enemies3[i].shape.getPosition().y + enemies3[i].shape.getGlobalBounds().height - 10)));
						enemies3[i].shootTimer2 = 0;
					}
				}

				for (size_t i = 0; i < enemies3.size(); i++)
				{

					for (size_t k = 0; k < enemies3[i].bullets2.size(); k++)
					{
						enemies3[i].bullets2[k].shape.move(0.f, 10.f);
					}

					//Collision bullets2 with screen
					for (size_t k = 0; k < enemies3[i].bullets2.size(); k++)
					{
						if (enemies3[i].bullets2[k].shape.getPosition().y >= 850)
						{
							enemies3[i].bullets2.erase(enemies3[i].bullets2.begin() + k);
							break;
						}
					}
					// end Collision bullets2 with screen

					//Collision Bullets2 with player
					if (player.score >= 30)
					{

						for (size_t k = 0; k < enemies3[i].bullets2.size(); k++)
						{
							if (enemies3[i].bullets2[k].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
							{
								enemies3[i].bullets2.erase(enemies3[i].bullets2.begin() + k);
								player.HP--;
								break;
							}
						}

					}
					//end Collision Bullets2 with player
				}
			}
			//end Shooting Bullet2 Enemy


			//Shooting Boss Bullet1 and Bullet2 
			if (player.score >= 100)
			{
				for (size_t i = 0; i < Boss.size(); i++)
				{
					if (Boss[i].shootTimerBoss1 <= 80)
					{
						Boss[i].shootTimerBoss1++;
					}
					else
					{
						Boss[i].BulletsBoss1.push_back(bullet3(&BulletBoss1Texture, Vector2f(Boss[i].shape.getPosition().x + 40, Boss[i].shape.getPosition().y + Boss[i].shape.getGlobalBounds().height - 10)));
						Boss[i].BulletsBoss2.push_back(bullet3(&BulletBoss2Texture, Vector2f(Boss[i].shape.getPosition().x + Boss[i].shape.getGlobalBounds().width - 40, Boss[i].shape.getPosition().y + Boss[i].shape.getGlobalBounds().height - 10)));
						Boss[i].shootTimerBoss1 = 0;
					}

					if (Boss[i].shootTimerBoss2 <= 160)
					{
						Boss[i].shootTimerBoss2++;
					}
					else
					{
						Boss[i].BulletsBoss3.push_back(Bullet4(&BulletBoss3Texture, Vector2f(Boss[i].shape.getPosition().x + 100, Boss[i].shape.getPosition().y + Boss[i].shape.getGlobalBounds().height - 10)));
						Boss[i].shootTimerBoss2 = 0;
					}

					if (Boss[i].shootTimerBoss3 <= 240)
					{
						Boss[i].shootTimerBoss3++;
					}
					else
					{
						Boss[i].BulletsBoss4.push_back(Bullet4(&BulletBoss4Texture, Vector2f(Boss[i].shape.getPosition().x + Boss[i].shape.getGlobalBounds().width - 100, Boss[i].shape.getPosition().y + Boss[i].shape.getGlobalBounds().height - 10)));
						Boss[i].shootTimerBoss3 = 0;
					}
				}

				for (size_t i = 0; i < Boss.size(); i++)
				{

					for (size_t k = 0; k < Boss[i].BulletsBoss1.size(); k++)
					{
						Boss[i].BulletsBoss1[k].shape.move(0.f, 7.f);

					}
					for (size_t k = 0; k < Boss[i].BulletsBoss2.size(); k++)
					{
						Boss[i].BulletsBoss2[k].shape.move(0.f, 7.f);
					}

					for (size_t k = 0; k < Boss[i].BulletsBoss3.size(); k++)
					{
						if (Boss[i].BulletsBoss3[k].shape.getPosition().x <= 0)
						{
							Boss[i].BulletsBoss3[k].dir = 1;
						}

						if (Boss[i].BulletsBoss3[k].shape.getPosition().x + Boss[i].BulletsBoss3[k].shape.getGlobalBounds().width >= window.getSize().x)
						{
							Boss[i].BulletsBoss3[k].dir = 0;
						}

						if (Boss[i].BulletsBoss3[k].dir == 1)
						{
							Boss[i].BulletsBoss3[k].shape.move(7.f, 3.f);
						}

						if (Boss[i].BulletsBoss3[k].dir == 0)
						{
							Boss[i].BulletsBoss3[k].shape.move(-8.f, 3.f);
						}

					}

					for (size_t k = 0; k < Boss[i].BulletsBoss4.size(); k++)
					{
						if (Boss[i].BulletsBoss4[k].shape.getPosition().x <= 0)
						{
							Boss[i].BulletsBoss4[k].dir = 1;
						}

						if (Boss[i].BulletsBoss4[k].shape.getPosition().x + Boss[i].BulletsBoss4[k].shape.getGlobalBounds().width >= window.getSize().x)
						{
							Boss[i].BulletsBoss4[k].dir = 0;
						}

						if (Boss[i].BulletsBoss4[k].dir == 1)
						{
							Boss[i].BulletsBoss4[k].shape.move(7.f, 3.f);
						}

						if (Boss[i].BulletsBoss4[k].dir == 0)
						{
							Boss[i].BulletsBoss4[k].shape.move(-8.f, 3.f);
						}

					}



					//Collision bullets3&4 with screen
					for (size_t k = 0; k < Boss[i].BulletsBoss1.size(); k++)
					{
						if (Boss[i].BulletsBoss1[k].shape.getPosition().y >= 850)
						{
							Boss[i].BulletsBoss1.erase(Boss[i].BulletsBoss1.begin() + k);
							break;
						}
					}
					for (size_t k = 0; k < Boss[i].BulletsBoss2.size(); k++)
					{
						if (Boss[i].BulletsBoss2[k].shape.getPosition().y >= 850)
						{
							Boss[i].BulletsBoss2.erase(Boss[i].BulletsBoss2.begin() + k);
							break;
						}
					}
					// end Collision bullets3&4 with screen

					for (size_t k = 0; k < Boss[i].BulletsBoss3.size(); k++)
					{
						if (Boss[i].BulletsBoss3[k].shape.getPosition().y >= 850)
						{
							Boss[i].BulletsBoss3.erase(Boss[i].BulletsBoss3.begin() + k);
							break;
						}

					}

					for (size_t k = 0; k < Boss[i].BulletsBoss4.size(); k++)
					{
						if (Boss[i].BulletsBoss4[k].shape.getPosition().y >= 850)
						{
							Boss[i].BulletsBoss4.erase(Boss[i].BulletsBoss4.begin() + k);
							break;
						}

					}

					//Collision Bullets3&4 with player
					if (player.score >= 100)
					{

						for (size_t k = 0; k < Boss[i].BulletsBoss1.size(); k++)
						{
							if (Boss[i].BulletsBoss1[k].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
							{
								Boss[i].BulletsBoss1.erase(Boss[i].BulletsBoss1.begin() + k);
								player.HP--;
								break;
							}
						}

						for (size_t k = 0; k < Boss[i].BulletsBoss2.size(); k++)
						{
							if (Boss[i].BulletsBoss2[k].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
							{
								Boss[i].BulletsBoss2.erase(Boss[i].BulletsBoss2.begin() + k);
								player.HP--;
								break;
							}
						}

						for (size_t k = 0; k < Boss[i].BulletsBoss3.size(); k++)
						{
							if (Boss[i].BulletsBoss3[k].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
							{
								Boss[i].BulletsBoss3.erase(Boss[i].BulletsBoss3.begin() + k);
								player.HP--;
								break;
							}
						}
						for (size_t k = 0; k < Boss[i].BulletsBoss4.size(); k++)
						{
							if (Boss[i].BulletsBoss4[k].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
							{
								Boss[i].BulletsBoss4.erase(Boss[i].BulletsBoss4.begin() + k);
								player.HP--;
								break;
							}

						}

					}
					//end Collision Bullets3&4 with player
				}
			}

			//End Shooting Boss Bullet1 and Bullet2




			if (player.score <= 15)
			{
				//Spawning Enemy1
				if (EnemySpawn1 < 45)
				{
					EnemySpawn1++;
				}

				if (EnemySpawn1 >= 45)
				{
					enemies1.push_back(Enemy1(&Enemy1Texture, window.getSize()));
					EnemySpawn1 = 0;

				}
				//end Spawning Enemy1
			}

			//Spawning Enemy2
			if (player.score > 15 && player.score <= 30)
			{
				if (EnemySpawn1 < 70)
				{
					EnemySpawn2++;
				}

				if (EnemySpawn2 >= 70)
				{
					enemies2.push_back(Enemy2(&Enemy2Texture, window.getSize()));
					EnemySpawn2 = 0;

				}
			}
			//end Spawning Enemy2

			//Spawning Enemy3
			if (player.score > 30 && player.score <= 60)
			{
				if (EnemySpawn3 < 70)
				{
					EnemySpawn3++;
				}

				if (EnemySpawn3 >= 70)
				{
					enemies3.push_back(Enemy3(&Enemy3Texture, window.getSize()));
					EnemySpawn3 = 0;
				}

			}
			//end Spawning Enemy3

			//Spawning Enemy4
			if (player.score >= 60 && player.score <= 80)
			{
				for (size_t i = 0; i < enemies3.size(); i++)
				{
					enemies3.erase(enemies3.begin() + i);
				}

				if (EnemySpawn4 < 25)
				{
					EnemySpawn4++;
				}

				if (EnemySpawn4 >= 25)
				{
					enemies4.push_back(Enemy4(&Enemy4Texture, window.getSize()));
					EnemySpawn4 = 0;
				}

			}
			//end Spawning Enemy4

			//Spawning Enemy5
			if (player.score >= 80 && player.score <= 100)
			{
				for (size_t i = 0; i < enemies4.size(); i++)
				{
					enemies4.erase(enemies4.begin() + i);
				}

				if (EnemySpawn5 < 25)
				{
					EnemySpawn5++;
				}

				if (EnemySpawn5 >= 25)
				{
					enemies5.push_back(Enemy5(&Enemy5Texture, window.getSize()));
					EnemySpawn5 = 0;
				}

			}
			//end Spawning Enemy5


			//Spawning boss
			if (player.score >= 100 && condition_boos == 0)
			{
				for (size_t i = 0; i < enemies5.size(); i++)
				{
					enemies5.erase(enemies5.begin() + i);
				}
				Boss.push_back(boss(&BossTexture, window.getSize()));
				condition_boos = 1;

			}

			//end spawning boos

			//Spawning star bonus
			if (StarSpawn < 400)
			{
				StarSpawn++;
			}

			if (StarSpawn >= 400)
			{
				stars.push_back(star(&StarTexture, window.getSize()));
				StarSpawn = 0;
			}
			//end spawning star bonus

			//Spawning heart bonus
			if (StarSpawn < 800)
			{
				HeartSpawn++;
			}

			if (HeartSpawn >= 800)
			{
				hearts.push_back(heart(&HeartTexture, window.getSize()));
				HeartSpawn = 0;
			}
			//end spawning star bonus



			if (player.score <= 15)
			{
				//Enemy1 collision
				for (size_t i = 0; i < enemies1.size(); i++)
				{
					enemies1[i].shape.move(0.f, 5.f);
					//Enemy1 collision with screen
					if (enemies1[i].shape.getPosition().y >= window.getSize().y)
					{
						enemies1.erase(enemies1.begin() + i);
						break;
					}
					//Enemy1 end collision with screen

					//Enemy1 collision with player
					if (enemies1[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{
						enemies1.erase(enemies1.begin() + i);
						player.score++;
						player.HP--;
						break;
					}
					//Enemy1 end collision with player

				}
				//Enemy1 end collision 
			}

			//Star bonus collision
			for (size_t i = 0; i < stars.size(); i++)
			{
				stars[i].shape.move(0.f, 6.f);
				//Stars collision with screen
				if (stars[i].shape.getPosition().y >= window.getSize().y)
				{
					stars.erase(stars.begin() + i);
					break;
				}
				//star end collision with screen

				//star collision with player
				if (stars[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					stars.erase(stars.begin() + i);
					player.score += 1;
					break;
				}
				//star end collision with player

			}
			//end Star bonus collision

			//Heart bonus collision
			for (size_t i = 0; i < hearts.size(); i++)
			{
				hearts[i].shape.move(0.f, 3.f);
				//Heart bonus collision with screen
				if (hearts[i].shape.getPosition().y >= window.getSize().y)
				{
					hearts.erase(hearts.begin() + i);
					break;
				}
				//end heart bonus collision with screen

				//Heart bonus collision with player
				if (player.HP <= 5)
				{
					if (hearts[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{
						hearts.erase(hearts.begin() + i);
						player.HP++;
						break;
					}
				}
				//end heart bonus collison with player
			}
			//end Heart bonus collision



			//Enemy2 collision
			if (player.score > 15 && player.score <= 30)
			{

				for (size_t i = 0; i < enemies2.size(); i++)
				{
					enemies2[i].shape.move(0.f, 11.f);
					//Enemy2 collision with screen
					if (enemies2[i].shape.getPosition().y >= window.getSize().y)
					{
						enemies2.erase(enemies2.begin() + i);
						break;
					}
					//Enemy2 end collision with screen

					//Enemy2 collision with player
					if (enemies2[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{
						enemies2.erase(enemies2.begin() + i);
						player.score += 1;
						player.HP--;
						break;
					}
					//Enemy2 end collision with player

				}
			}
			//Enemy2 end collision 

			//Enemies3 collision
			if (player.score > 30 && player.score <= 60)
			{

				for (size_t i = 0; i < enemies3.size(); i++)
				{
					enemies3[i].shape.move(0.f, 3.f);
					//Enemy3 collision with screen
					if (enemies3[i].shape.getPosition().y >= window.getSize().y)
					{
						enemies3.erase(enemies3.begin() + i);
						break;
					}
					//Enemy3 end collision with screen

					//Enemy3 collision with player
					if (enemies3[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{
						enemies3.erase(enemies3.begin() + i);
						player.score += 1;
						player.HP -= 1;
						break;
					}
					//Enemy3 end collision with player

				}
			}
			//end Enemies3 collision

			//Enemies4 collision
			if (player.score >= 60 && player.score <= 80)
			{

				for (size_t i = 0; i < enemies4.size(); i++)
				{

					//Enemy4 collision with screen
					if (enemies4[i].shape.getPosition().x <= 0)
					{
						enemies4[i].dir = 1;

					}

					if (enemies4[i].shape.getPosition().x + enemies4[i].shape.getGlobalBounds().width >= window.getSize().x)
					{
						enemies4[i].dir = 0;

					}
					if (enemies4[i].dir == 1)
					{
						enemies4[i].shape.move(7.f, 5.f);
					}

					if (enemies4[i].dir == 0)
					{
						enemies4[i].shape.move(-8.f, 6.f);
					}

					if (enemies4[i].shape.getPosition().y >= window.getSize().y)
					{
						enemies4.erase(enemies4.begin() + i);
						break;
					}
					//Enemy4 end collision with screen

					//Enemy4 collision with player
					if (enemies4[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{
						enemies4.erase(enemies4.begin() + i);
						player.score += 1;
						player.HP -= 2;
						break;
					}
					//Enemy4 end collision with player
				}
			}
			//end Enemies4 collision

			//Enemies5 collision
			if (player.score >= 80 && player.score <= 100)
			{

				for (size_t i = 0; i < enemies5.size(); i++)
				{

					//Enemy5 collision with screen
					if (enemies5[i].shape.getPosition().x <= 0)
					{
						enemies5[i].dir = 1;

					}

					if (enemies5[i].shape.getPosition().x + enemies5[i].shape.getGlobalBounds().width >= window.getSize().x)
					{
						enemies5[i].dir = 0;

					}
					if (enemies5[i].dir == 1)
					{
						enemies5[i].shape.move(10.f, 5.f);
					}

					if (enemies5[i].dir == 0)
					{
						enemies5[i].shape.move(-10.f, 5.f);
					}

					if (enemies5[i].shape.getPosition().y >= window.getSize().y)
					{
						enemies5.erase(enemies5.begin() + i);
						break;
					}
					//Enemy5 end collision with screen

					//Enemy5 collision with player
					if (enemies5[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{
						enemies5.erase(enemies5.begin() + i);
						player.score += 1;
						player.HP -= 2;
						break;
					}
					//Enemy5 end collision with player
				}
			}
			//end Enemies5 collision

			//Boss collision
			if (player.score >= 100)
			{

				for (size_t i = 0; i < enemies5.size(); i++)
				{
					enemies5.erase(enemies5.begin() + i);
				}


				for (size_t i = 0; i < Boss.size(); i++)
				{
					Boss[i].shape.move(0.f, 0.15f);
					//Boss collision with player = end game
					if (Boss[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{
						Boss.erase(Boss.begin() + i);
						state = END;
						break;
					}
					//Boss end collision with player = end game 
				}
			}

			//end Boss collision


			//displaying score
			Score.setString("Score: " + std::to_string(player.score));
			//end displaying score

			//displaying hp
			HpText.setString("HP: " + std::to_string(player.HP));
			//end displaying hp





			window.clear();
			window.draw(map);
			window.draw(player.shape);

			for (size_t i = 0; i < player.bullets1.size(); i++)
			{
				window.draw(player.bullets1[i].shape);
			}
			if (player.score <= 15)
			{
				for (size_t i = 0; i < enemies1.size(); i++)
				{
					window.draw(enemies1[i].shape);
				}
			}

			if (player.score >= 15 && player.score <= 30)
			{
				for (size_t i = 0; i < enemies2.size(); i++)
				{
					window.draw(enemies2[i].shape);
				}
			}

			for (size_t i = 0; i < stars.size(); i++)
			{
				window.draw(stars[i].shape);
			}
			for (size_t i = 0; i < hearts.size(); i++)
			{
				window.draw(hearts[i].shape);
			}

			if (player.score >= 30 && player.score <= 60)
			{
				for (size_t i = 0; i < enemies3.size(); i++)
				{
					window.draw(enemies3[i].shape);
				}
			}

			if (player.score >= 30 && player.score <= 60)
			{
				for (size_t i = 0; i < enemies3.size(); i++)
				{
					for (size_t k = 0; k < enemies3[i].bullets2.size(); k++)
					{
						window.draw(enemies3[i].bullets2[k].shape);
					}
				}
			}

			if (player.score >= 60 && player.score <= 80)
			{
				for (size_t i = 0; i < enemies4.size(); i++)
				{
					window.draw(enemies4[i].shape);
				}
			}

			if (player.score <= 100 && player.score >= 80)
			{
				for (size_t i = 0; i < enemies5.size(); i++)
				{
					window.draw(enemies5[i].shape);
				}
			}
			if (player.score >= 100)
			{
				for (size_t i = 0; i < Boss.size(); i++)
				{
					window.draw(Boss[i].shape);
				}

			}

			if (player.score >= 100)
			{
				for (size_t i = 0; i < Boss.size(); i++)
				{
					for (size_t k = 0; k < Boss[i].BulletsBoss1.size(); k++)
					{
						window.draw(Boss[i].BulletsBoss1[k].shape);
					}
				}
				for (size_t i = 0; i < Boss.size(); i++)
				{
					for (size_t k = 0; k < Boss[i].BulletsBoss2.size(); k++)
					{
						window.draw(Boss[i].BulletsBoss2[k].shape);
					}
				}
				for (size_t i = 0; i < Boss.size(); i++)
				{
					for (size_t k = 0; k < Boss[i].BulletsBoss3.size(); k++)
					{
						window.draw(Boss[i].BulletsBoss3[k].shape);
					}
				}
				for (size_t i = 0; i < Boss.size(); i++)
				{
					for (size_t k = 0; k < Boss[i].BulletsBoss4.size(); k++)
					{
						window.draw(Boss[i].BulletsBoss4[k].shape);
					}
				}
			}



			window.draw(Score);
			window.draw(HpText);

			window.display();

		}
		else
		{
			Sprite shape;
			Texture BlackScreen;
			Text nick;
			nick.setFont(font);
			nick.setCharacterSize(40);
			nick.setFillColor(sf::Color::White);
			nick.setPosition(window.getSize().x/2-190, window.getSize().y/2-45);
			nick.setString(NamePlayer);
			Text score_end;
			score_end.setFont(font);
			score_end.setCharacterSize(34);
			score_end.setPosition(390, 490);
			score_end.setString(std::to_string(player.score));
			BlackScreen.loadFromFile("Black.png");
			shape.setTexture(BlackScreen);
			window.clear();
			window.draw(background);
			window.draw(score_end);
			//window.draw(shape);
			window.draw(nick);
			window.display();

		}
		
	}
	
	


	
}