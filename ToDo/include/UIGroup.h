#include <string>

extern "C"  {
	typedef struct UIGroupProps {
		//uint32 ID;
		uint Orientation;
		bool SpaceOuter;
		bool SpaceInner;
	} UIGroupProps;
}

class UIGroup {
private:
	UIGroupProps _props;
	struct Gadget *_gadget;
	//uint32 _ID;
	uint _Orientation;
	bool _SpaceOuter;
	bool _SpaceInner;

public:
	UIGroup():
		_gadget(NULL),
		//_ID(0),
		_Orientation(LAYOUT_ORIENT_VERT),
		_SpaceOuter(FALSE),
		_SpaceInner(FALSE) { }

	UIGroup(UIGroupProps props) {
		_props = props;
	}

	struct Gadget *gadget() {
		if (_gadget) return _gadget;

		_gadget = (struct Gadget *) IIntuition->NewObject(
			ILayout->LAYOUT_GetClass(),
			NULL,
			LAYOUT_Orientation,  LAYOUT_ORIENT_VERT,
			LAYOUT_SpaceOuter,   TRUE,
          	LAYOUT_SpaceInner,   TRUE,
			TAG_DONE
		);

		return _gadget;
	}

	void addMember(APTR gadgetToAdd) {
		struct Gadget* groupGadget = gadget();
		struct opMember opAddMember_s = {
			MethodID : OM_ADDMEMBER,
			opam_Object : (Object*)gadgetToAdd
		};
		//IIntuition->IDoMethod(groupGadget, OM_ADDMEMBER, &opAddMember_s);

	}
	~UIGroup() {

	}
};
