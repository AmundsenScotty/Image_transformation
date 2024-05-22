#include <iostream>

#include "image.h"
#include "states.h"
#include "point.h"

#define MEMTRACE
#include "memtrace.h"

//// State class

	Image* State::base = nullptr;
	Image* State::in_progress = nullptr;

	State::~State() {}

	Image* State::getBase()
	{
		return base;
	}

	void State::setBase(Image* ip)
	{
		base = ip;
	}

	Image* State::getInProgress()
	{
		return in_progress;
	}

	void State::setInProgress(Image* ip)
	{
		delete in_progress;
		in_progress = ip;
	}

////


//// Start state

	unsigned Start::choice = 0;

	Start::Start()
	{
		State::setBase(nullptr);
		State::setInProgress(nullptr);
	}

	void Start::run() const
	{
		system("cls");

		std::cout << "�dv�zl�m a k�p transzform�ci�s programban!!!" << std::endl << std::endl;
		std::cout << "K�rem v�lasszon az al�bbi opci�k k�z�l az opci� sz�m�nak megad�s�val!" << std::endl;
		std::cout << "1. K�p beolvas�sa" << std::endl;
		std::cout << "2. Pelda k�pek" << std::endl;
		std::cout << "Sorsz�m: ";
	
		std::cin >> choice;

		if (choice == 0 || choice > 2)
			throw std::exception("Helytelen sz�m!");
	}

	State* Start::next_state() const
	{
		switch (choice)
		{
		case 1:
			return new Read_file;
			break;
		case 2:
			return new Example;
			break;
		}
	}

////


//// Read image file

	void Read_file::run() const
	{
		system("cls");

		std::cout << "K�rem adja meg a file nev�t: ";

		std::string fileName;

		std::cin >> fileName;
		
		Image::check_file_name(fileName);

		State::setBase(new Image(fileName));
		State::setInProgress(new Image(fileName));
	}

	State* Read_file::next_state() const
	{
		return new Select_corners;
	}

////


//// Open example file and select example corners

	void Example::run() const
	{
		system("cls");

		std::cout << "K�rem v�lasszon az al�bbi p�lda f�jlok k�z�l az opci� sz�m�nak megad�s�val!" << std::endl;
		std::cout << "1. example1.jpg" << std::endl;
		std::cout << "2. example2.jpg" << std::endl;
		std::cout << "Sorsz�m: " << std::endl;

		unsigned choice = 0;

		std::cin >> choice;

		if (choice == 0 || choice > 2)
			throw std::exception("Helytelen sz�m!");

		State::setBase(new Image("example" + std::to_string(choice) + ".jpg"));
		State::setInProgress(new Image("example" + std::to_string(choice) + ".jpg"));

		State::getInProgress()->print_parameters();

		// Example corner selection
		switch (choice)
		{
			case 1:
				std::cout << "P�lda t�glalap 1 / 2? " << std::endl;
				unsigned rectangle_choice;
				std::cin >> rectangle_choice;

				switch (rectangle_choice)
				{
				case 1:
					State::getInProgress()->set_corner(0, Point(367, 491));
					State::getInProgress()->set_corner(1, Point(40, 491));
					State::getInProgress()->set_corner(2, Point(248, 126));
					State::getInProgress()->set_corner(3, Point(578, 126));
					break;

				case 2:
					State::getInProgress()->set_corner(0, Point(577, 1333));
					State::getInProgress()->set_corner(1, Point(248, 1333));
					State::getInProgress()->set_corner(2, Point(39, 967));
					State::getInProgress()->set_corner(3, Point(367, 967));
					break;

				default:
					throw std::exception("Helytelen v�laszt�s!");
				}
			break;
		case 2:
			State::getInProgress()->set_corner(0, Point(350, 600));
			State::getInProgress()->set_corner(1, Point(200, 600));
			State::getInProgress()->set_corner(2, Point(150, 200));
			State::getInProgress()->set_corner(3, Point(450, 200));
			break;

		default:
			throw std::exception("Helytelen v�laszt�s!");
		}
	}

	State* Example::next_state() const
	{
		return new Transform;
	}

////


//// Select corners for transformation

	void Select_corners::run() const
	{

		for (int i = 0; i < 4; i++)
		{
			system("cls");

			State::getBase()->print_parameters();

			std::cout << "Adja meg a transzform�lni k�v�t t�glalap sarkait, a koordin�t�kat sz�k�zzel elv�lasztva!" << std::endl << std::endl;

			std::cout << "Eddig be�ll�tott �rt�kek: " << std::endl;
			for (int i = 0; i < 4; i++)
				std::cout << i + 1 << ". sarok: (" << State::getInProgress()->get_corners()[i].x << ", "
				<< State::getInProgress()->get_corners()[i].y << ")" << std::endl;
			std::cout << std::endl;

			std::cout << i + 1 << ".sarok be�ll�t�sa: ";
			try {
				Point current_corner;

				std::cin >> current_corner;

				State::getBase()->in_frame(current_corner);

				std::cout << "x: " << current_corner.x << " y: " << current_corner.y << std::endl;

				State::getInProgress()->set_corner(i, current_corner);

			}
			catch (std::exception const& err)
			{
				i--;
				std::cout << "Hiba: " << err.what() << std::endl;
				std::cout << "K�rem pr�b�lja �jra!" << std::endl << std::endl;
				prompt_next();
			}
		}

		/// Feedback

			system("cls");

			std::cout << "A be�ll�tott �rt�kek: " << std::endl;
			for (int i = 0; i < 4; i++)
				std::cout << i + 1 << ". sarok: (" << State::getInProgress()->get_corners()[i].x << ", "
				<< State::getInProgress()->get_corners()[i].y << ")" << std::endl;
			std::cout << std::endl;

			std::cout << "K�r seg�dfunkci�t?" << std::endl;
			std::cout << "1. Nem" << std::endl;
			std::cout << "2. Sarkok kirajzol�sa" << std::endl;
			std::cout << "3. N�gysz�g kirajzol�sa" << std::endl;

			unsigned choice_num = 0;

			std::cin >> choice_num;

			switch (choice_num)
			{
				case 1:
					break;
				case 2:
					State::setInProgress(State::getInProgress()->draw_corners(State::getInProgress()->get_corners()));
					State::getInProgress()->write_image_to_file();
					State::getInProgress()->open_image_window();
					break;

				case 3:
					State::setInProgress(State::getInProgress()->draw_rectangle(State::getInProgress()->get_corners()));
					State::getInProgress()->write_image_to_file();
					State::getInProgress()->open_image_window();
					break;
			}

			std::cout << "Megfelel a kiv�lasztott t�glalap?" << std::endl;
			std::cout << "V�lasz (i / n): " << std::endl;

			char choice = 0;

			std::cin >> choice;

			switch (choice)
			{
			case 'i':
				break;

			case 'n':
				throw std::exception("V�laszt�s �jraindul!");
				break;

			default:
				throw std::exception("Helytelen v�laszt�s!");
			}

		///
	}

	State* Select_corners::next_state() const
	{
		return new Transform;
	}

////


//// Transformation

	void Transform::run() const
	{
		State::setInProgress(State::getBase()->extract_rectangle(State::getInProgress()->get_corners()));
	}

	State* Transform::next_state() const
	{
		return new End();
	}

////


//// End

	End::~End()
	{
		delete State::getBase();
		delete State::getInProgress();
	}

	void End::run() const
	{
		State::getInProgress()->write_image_to_file("...", 100, true);

		std::cout << "A f�jl ment�sre ker�lt " << State::getInProgress()->get_file_name() << " n�ven." << std:: endl; // TODO: print filename

		std::cout << "K�sz�n�m, hogy programomat v�lasztotta!!!" << std::endl;

		State::getInProgress()->open_image_window();
	}

	State* End::next_state() const
	{
		return nullptr;
	}

////


//// Prompt next

	void prompt_next()
	{
		std::cout << std::endl;
		std::cout << "Folytat�shoz nyomjon egy billenty�t! ...";
		std::cin.ignore();
		getchar();
	}

////