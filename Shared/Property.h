#pragma once

//
// By value
//

#define Setter(type, name) \
	void name##_set(type value)

#define ISetter(type, name) \
	virtual Setter(type, name) = 0

#define Getter(type, name) \
	type name##_get(void)

#define IGetter(type, name) \
	virtual Getter(type, name) = 0

#define GetSet(type, name) \
    Getter(type, name); \
    Setter(type, name)

//
// By reference
// 

#define SetterRef(type, name) \
	void name##_set(type &value)

#define ISetterRef(type, name) \
    virtual SetterRef(type, name) = 0

#define GetterRef(type, name) \
    type &name##_get(void)

#define IGetterRef(type, name) \
    virtual GetterRef(type, name) = 0

#define GetSetRef(type, name) \
    GetterRef(type, name); \
    SetterRef(type, name)

//
// Property
// 

#define PropertyRW(type, name) \
	__declspec(property(get = name##_get, put = name##_set)) type name

#define PropertyR(type, name) \
	__declspec(property(get = name##_get)) type name

#define PropertyW(type, name) \
	__declspec(property(set = name##_set)) type name