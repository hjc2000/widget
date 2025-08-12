#include "Button.h" // IWYU pragma: keep

void widget::Button::ConnectSignal()
{
	QMetaObject::Connection connection;

	connection = connect(this,
						 &QPushButton::clicked,
						 [this]()
						 {
							 OnClicked();
						 });

	_connections.push_back(connection);

	connection = connect(this,
						 &QPushButton::pressed,
						 [this]()
						 {
							 OnPressed();
						 });

	_connections.push_back(connection);

	connection = connect(this,
						 &QPushButton::released,
						 [this]()
						 {
							 OnReleased();
						 });

	_connections.push_back(connection);
}
