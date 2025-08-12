#include "ComboBox.h" // IWYU pragma: keep

void widget::ComboBox::ConnectSignals()
{
	QMetaObject::Connection connection;

	{
		connection = connect(&_combo_box,
							 &QComboBox::currentIndexChanged,
							 [this](int index)
							 {
								 _current_index_changed.Invoke(index);
							 });

		_connections.push_back(connection);
	}

	{
		connection = connect(&_combo_box,
							 &QComboBox::currentTextChanged,
							 [this](QString const &text)
							 {
								 _current_text_changed.Invoke(base::to_string(text));
							 });

		_connections.push_back(connection);
	}
}
