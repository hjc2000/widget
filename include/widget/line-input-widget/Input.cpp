#include "Input.h" // IWYU pragma: keep

void widget::Input::ConnectSignal()
{
	QMetaObject::Connection connection;

	connection = connect(_line_edit,
						 &QLineEdit::textChanged,
						 [this]()
						 {
							 try
							 {
								 _text_changed_event.Invoke(_line_edit->text());
							 }
							 catch (std::exception const &e)
							 {
							 }
							 catch (...)
							 {
							 }
						 });

	_connections.push_back(connection);

	connection = connect(_line_edit,
						 &QLineEdit::textEdited,
						 [this]()
						 {
							 try
							 {
								 _text_edited_event.Invoke(_line_edit->text());
							 }
							 catch (std::exception const &e)
							 {
							 }
							 catch (...)
							 {
							 }
						 });

	_connections.push_back(connection);

	connection = connect(_line_edit,
						 &QLineEdit::editingFinished,
						 [this]()
						 {
							 try
							 {
								 _text_editing_finished_event.Invoke(_line_edit->text());
							 }
							 catch (std::exception const &e)
							 {
							 }
							 catch (...)
							 {
							 }

							 try
							 {
								 _text_changing_finished_event.Invoke(_line_edit->text());
							 }
							 catch (std::exception const &e)
							 {
							 }
							 catch (...)
							 {
							 }
						 });

	_connections.push_back(connection);
}
