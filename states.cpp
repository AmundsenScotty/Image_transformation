#include <iostream>

#include "image.h"
#include "states.h"

//// State class

	enum States State::currentState = Start_state;

	Image* State::base = nullptr;
	Image* State::in_progress = nullptr;

	State::~State()
	{
	}

	void State::restart() const
	{
		currentState = Start_state;
	}

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
		in_progress = ip;
	}

	unsigned State::getState()
	{
		return currentState;
	}

	void State::setState(enum States s)
	{
		currentState = s;
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

		std::cout << "Üdvözlöm a kép transzformációs programban!!!" << std::endl << std::endl;
		std::cout << "Kérem válasszon az alábbi opciók közül az opció számának megadásával!" << std::endl;
		std::cout << "1. Kép beolvasása" << std::endl;
		std::cout << "2. Pelda képek" << std::endl;
		std::cout << "Sorszám: " << std::endl;
	
		std::cin >> choice;

		if (choice == 0 || choice > 2)
			throw std::exception("Helytelen szám!");
	}

	void Start::restart() const
	{
		choice = 0;
		setState(Start_state);
	}

	void Start::next_state() const
	{
		switch (choice)
		{
		case 1:
			State::setState(Read_file_state);
			break;
		case 2:
			State::setState(Example_state);
			break;
		}
	}

////


//// Read image file

	void Read_file::run() const
	{
		system("cls");

		std::cout << "Kérem adja meg a file nevét: ";

		std::string fileName;

		std::cin >> fileName;

		try
		{
			Image::check_file_name(fileName);
		}
		catch (std::exception const& err)
		{
			std::cout << "Hiba: " << err.what() << std::endl;
			std::cout << "Kérem próbálja újra!" << std::endl;
		}

		State::setBase(new Image(fileName));

		State::getBase()->print_parameters();
	}

	void Read_file::restart() const
	{
		setState(Read_file_state);
	}

	void Read_file::next_state() const
	{
		setState(Select_corners_state);
	}

////


//// Open example file and select example corners

	void Example::run() const
	{
		system("cls");

		std::cout << "Kérem válasszon az alábbi példa fájlok közül az opció számának megadásával!" << std::endl;
		std::cout << "1. example1.jpg" << std::endl;
		std::cout << "2. example2.jpg" << std::endl;
		std::cout << "Sorszám: " << std::endl;

		unsigned choice = 0;

		std::cin >> choice;

		if (choice == 0 || choice > 2)
			throw std::exception("Helytelen szám!");

		State::setBase(new Image("example" + std::to_string(choice) + ".jpg"));
		State::setInProgress(new Image("example" + std::to_string(choice) + ".jpg"));

		State::getInProgress()->print_parameters();

		// Example corner selection
		switch (choice)
		{
			case 1:
				std::cout << "Példa téglalap 1 / 2? " << std::endl;
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
					throw std::exception("Helytelen választás!");
				}
			break;
		case 2:
			State::getInProgress()->set_corner(0, Point(350, 600));
			State::getInProgress()->set_corner(1, Point(200, 600));
			State::getInProgress()->set_corner(2, Point(150, 200));
			State::getInProgress()->set_corner(3, Point(450, 200));
			break;

		default:
			throw std::exception("Helytelen választás!");
		}
	}

	void Example::restart() const
	{
		setState(Example_state);
	}

	void Example::next_state() const
	{
		setState(Transform_state);
	}

////


//// Select corners for transformation

	void Select_corners::run() const
	{

		system("cls");

		std::cout << "Adja meg a transzformálni kívát téglalap sarkait, a koordinátákat szóközzel elválasztva!" << std::endl << std::endl;

		Point corners[4];

		for (int i = 0; i < 4; i++)
		{
			std::cout << i + 1 << ".sarok: ";
			try {
				std::cin >> corners[i];

				State::getBase()->in_frame(corners[i]);

				std::cout << "x: " << corners[i].x << " y: " << corners[i].y << std::endl;
			}
			catch (std::exception const& err)
			{
				std::cout << "Hiba: " << err.what() << std::endl;
				std::cout << "Kérem próbálja újra!" << std::endl;
				i--;
			}
		}

		/// Checkup

			std::cout << "Megfelel a kiválasztott téglalap?" << std::endl;
			std::cout << "Válasz (i / n): " << std::endl;

			char choice = 0;

			std::cin >> choice;

			switch (choice)
			{
			case 'i':
				break;

			case 'n':
				Select_corners::restart();
				break;

			default:
				throw std::exception("Helytelen választás!");
			}

		///
	}

	void Select_corners::restart() const
	{
		setState(Select_corners_state);
	}

	void Select_corners::next_state() const
	{
		setState(Transform_state);
	}

////


//// Transformation

	void Transform::run() const
	{
		Point* corners = new Point[4];

		for (int i = 0; i < 4; i++)
			corners[i] = State::getInProgress()->get_corners()[i];

		delete State::getInProgress();

		State::setInProgress(State::getBase()->extract_rectangle(corners));

		delete[] corners;
	}

	void Transform::restart() const
	{
		setState(Transform_state);
	}

	void Transform::next_state() const
	{
		setState(End_state);
	}

////


//// End

	End::~End()
	{
		//delete State::getBase();
		//delete State::getInProgress();
	}

	void End::run() const
	{
		State::getInProgress()->write_image_to_file("...", 100, true);

		std::cout << "A fájl mentésre került " << State::getInProgress()->get_file_name() << " néven." << std:: endl; // TODO: print filename

		std::cout << "Köszönöm, hogy programomat választotta!!!" << std::endl;

		State::getInProgress()->open_image_window();
	}

	void End::restart() const
	{
		setState(End_state);
	}

	void End::next_state() const
	{
		setState(Finish_state);

		delete State::getInProgress();
		delete State::getBase();
	}

////