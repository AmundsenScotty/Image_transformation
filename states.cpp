#include <iostream>

#include "image.h"
#include "states.h"
#include "point.h"

#define MEMTRACE
#include "memtrace.h"

//// State class

/// @brief The base image for the state.
Image* State::base = nullptr;

/// @brief The in-progress image for the state.
Image* State::in_progress = nullptr;

/// @brief Destructor for the State class.
State::~State() {}

/// @brief Gets the base image.
/// @return A pointer to the base image.
Image* State::getBase()
{
	return base;
}

/// @brief Sets the base image.
/// @param ip A pointer to the new base image.
void State::setBase(Image* ip)
{
	base = ip;
}

/// @brief Gets the in-progress image.
/// @return A pointer to the in-progress image.
Image* State::getInProgress()
{
	return in_progress;
}

/// @brief Sets the in-progress image.
/// @param ip A pointer to the new in-progress image.
void State::setInProgress(Image* ip)
{
	delete in_progress;
	in_progress = ip;
}

////

//// Start state

/// @brief The user's choice in the Start state.
unsigned Start::choice = 0;

/// @brief Constructor for the Start state.
Start::Start()
{
	State::setBase(nullptr);
	State::setInProgress(nullptr);
}

/// @brief Runs the Start state, prompting the user to make a choice.
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

/// @brief Determines the next state based on the user's choice.
/// @return A pointer to the next state.
State* Start::next_state() const
{
	switch (choice)
	{
	case 1:
		return new Read_file;
	case 2:
		return new Example;
	default:
		throw std::exception("Helytelen sz�m!");
	}
}

////

//// Read image file

/// @brief Runs the Read_file state, prompting the user to input the file name.
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

/// @brief Determines the next state after reading the file.
/// @return A pointer to the next state.
State* Read_file::next_state() const
{
	return new Select_corners;
}

////

//// Open example file and select example corners

/// @brief Runs the Example state, prompting the user to select an example file and corners.
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

/// @brief Determines the next state after selecting an example.
/// @return A pointer to the next state.
State* Example::next_state() const
{
	return new Transform;
}

////


//// Select corners for transformation

/// @brief Runs the Select_corners state, prompting the user to select corners for transformation.
void Select_corners::run() const
{
	for (int i = 0; i < 4; i++)
	{
		system("cls");

		State::getBase()->print_parameters();

		std::cout << "Adja meg a transzform�lni k�v�nt t�glalap sarkait, a koordin�t�kat sz�k�zzel elv�lasztva!" << std::endl << std::endl;

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

/// @brief Determines the next state after selecting corners.
/// @return A pointer to the next state.
State* Select_corners::next_state() const
{
	return new Transform;
}

////
//// Transformation

/// @brief Runs the Transform state, extracting a rectangle from the base image using the selected corners.
void Transform::run() const
{
	State::setInProgress(State::getBase()->extract_rectangle(State::getInProgress()->get_corners()));
}

/// @brief Determines the next state after the transformation.
/// @return A pointer to the End state.
State* Transform::next_state() const
{
	return new End();
}

////


//// End

/// @brief Destructor for the End state, responsible for deallocating memory of base and in-progress images.
End::~End()
{
	delete State::getBase();
	delete State::getInProgress();
}

/// @brief Runs the End state, saving the in-progress image to a file and displaying a closing message.
void End::run() const
{
	State::getInProgress()->write_image_to_file("...", 100, true);

	std::cout << "A f�jl ment�sre ker�lt " << State::getInProgress()->get_file_name() << " n�ven." << std::endl; // TODO: print filename

	std::cout << "K�sz�n�m, hogy programomat v�lasztotta!!!" << std::endl;

	State::getInProgress()->open_image_window();
}

/// @brief Determines the next state after the End state.
/// @return A nullptr since there is no next state after the End state.
State* End::next_state() const
{
	return nullptr;
}

////


//// Prompt next

/// @brief Prompts the user to continue by pressing a key.
void prompt_next()
{
	std::cout << std::endl;
	std::cout << "Folytat�shoz nyomjon egy billenty�t! ...";
	std::cin.ignore();
	getchar();
}

////
