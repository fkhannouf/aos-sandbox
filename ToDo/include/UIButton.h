#include <string>

extern "C"  {
	typedef struct UIButtonProps {
		uint32 ID;
		bool RelVerify;
		const char * Text;
	} UIButtonProps;
}

class UIButton {
private:
	UIButtonProps _props;
	struct Gadget *_gadget;
	uint32 _ID;
	bool _RelVerify;
	std::string _Text;

public:
	UIButton():
		_gadget(NULL),
		_ID(0),
		_RelVerify(FALSE),
		_Text("Default Label") { }

	UIButton(UIButtonProps props) {
		_props = props;
		if (props.Text) {
			_Text = std::string(props.Text);
		}
	}

	struct Gadget *gadget() {
		if (_gadget) return _gadget;

		_gadget = (struct Gadget *) IIntuition->NewObject(
			IButton->BUTTON_GetClass(),
			NULL,
			GA_ID,	_props.ID,
			GA_RelVerify, _props.RelVerify,
			GA_Text, _Text.c_str(),
			TAG_DONE
		);

		return _gadget;
	}

	~UIButton() {

	}
};
