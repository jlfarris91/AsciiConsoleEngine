#define DeclareEnum1(name, item1) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1 \
       }; \
       static const unsigned Count = 1u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum1(name, item1) \
   const name::Type name::Values[1] = { \
		0 \
   }; \
   const char *name::Names[1] = { \
		#item1 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum2(name, item1, item2) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2 \
       }; \
       static const unsigned Count = 2u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum2(name, item1, item2) \
   const name::Type name::Values[2] = { \
		0, 1 \
   }; \
   const char *name::Names[2] = { \
		#item1, #item2 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum3(name, item1, item2, item3) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3 \
       }; \
       static const unsigned Count = 3u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum3(name, item1, item2, item3) \
   const name::Type name::Values[3] = { \
		0, 1, 2 \
   }; \
   const char *name::Names[3] = { \
		#item1, #item2, #item3 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum4(name, item1, item2, item3, item4) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4 \
       }; \
       static const unsigned Count = 4u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum4(name, item1, item2, item3, item4) \
   const name::Type name::Values[4] = { \
		0, 1, 2, 3 \
   }; \
   const char *name::Names[4] = { \
		#item1, #item2, #item3, #item4 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum5(name, item1, item2, item3, item4, item5\
					 ) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5\
			 \
       }; \
       static const unsigned Count = 5u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum5(name, item1, item2, item3, item4, item5\
					) \
   const name::Type name::Values[5] = { \
		0, 1, 2, 3, 4 \
   }; \
   const char *name::Names[5] = { \
		#item1, #item2, #item3, #item4, #item5\
		 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum6(name, item1, item2, item3, item4, item5, \
					 item6) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6 \
       }; \
       static const unsigned Count = 6u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum6(name, item1, item2, item3, item4, item5, \
					item6) \
   const name::Type name::Values[6] = { \
		0, 1, 2, 3, 4, 5 \
   }; \
   const char *name::Names[6] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum7(name, item1, item2, item3, item4, item5, \
					 item6, item7) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7 \
       }; \
       static const unsigned Count = 7u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum7(name, item1, item2, item3, item4, item5, \
					item6, item7) \
   const name::Type name::Values[7] = { \
		0, 1, 2, 3, 4, 5, 6 \
   }; \
   const char *name::Names[7] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum8(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8 \
       }; \
       static const unsigned Count = 8u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum8(name, item1, item2, item3, item4, item5, \
					item6, item7, item8) \
   const name::Type name::Values[8] = { \
		0, 1, 2, 3, 4, 5, 6, 7 \
   }; \
   const char *name::Names[8] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum9(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9 \
       }; \
       static const unsigned Count = 9u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum9(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9) \
   const name::Type name::Values[9] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8 \
   }; \
   const char *name::Names[9] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum10(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10\
					 ) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10\
			 \
       }; \
       static const unsigned Count = 10u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum10(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10\
					) \
   const name::Type name::Values[10] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9\
		 \
   }; \
   const char *name::Names[10] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10\
		 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum11(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11 \
       }; \
       static const unsigned Count = 11u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum11(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11) \
   const name::Type name::Values[11] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10 \
   }; \
   const char *name::Names[11] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum12(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12 \
       }; \
       static const unsigned Count = 12u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum12(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12) \
   const name::Type name::Values[12] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11 \
   }; \
   const char *name::Names[12] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum13(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13 \
       }; \
       static const unsigned Count = 13u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum13(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13) \
   const name::Type name::Values[13] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12 \
   }; \
   const char *name::Names[13] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum14(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14 \
       }; \
       static const unsigned Count = 14u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum14(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14) \
   const name::Type name::Values[14] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13 \
   }; \
   const char *name::Names[14] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum15(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15\
					 ) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15\
			 \
       }; \
       static const unsigned Count = 15u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum15(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15\
					) \
   const name::Type name::Values[15] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14 \
   }; \
   const char *name::Names[15] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15\
		 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum16(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16 \
       }; \
       static const unsigned Count = 16u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum16(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16) \
   const name::Type name::Values[16] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15 \
   }; \
   const char *name::Names[16] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum17(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17 \
       }; \
       static const unsigned Count = 17u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum17(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17) \
   const name::Type name::Values[17] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16 \
   }; \
   const char *name::Names[17] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum18(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18 \
       }; \
       static const unsigned Count = 18u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum18(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18) \
   const name::Type name::Values[18] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17 \
   }; \
   const char *name::Names[18] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum19(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19 \
       }; \
       static const unsigned Count = 19u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum19(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19) \
   const name::Type name::Values[19] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18 \
   }; \
   const char *name::Names[19] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum20(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20\
					 ) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20\
			 \
       }; \
       static const unsigned Count = 20u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum20(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20\
					) \
   const name::Type name::Values[20] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19\
		 \
   }; \
   const char *name::Names[20] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20\
		 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum21(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21 \
       }; \
       static const unsigned Count = 21u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum21(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21) \
   const name::Type name::Values[21] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20 \
   }; \
   const char *name::Names[21] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum22(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22 \
       }; \
       static const unsigned Count = 22u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum22(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22) \
   const name::Type name::Values[22] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21 \
   }; \
   const char *name::Names[22] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum23(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23 \
       }; \
       static const unsigned Count = 23u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum23(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23) \
   const name::Type name::Values[23] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22 \
   }; \
   const char *name::Names[23] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum24(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23, item24) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23, item24 \
       }; \
       static const unsigned Count = 24u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum24(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23, item24) \
   const name::Type name::Values[24] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22, 23 \
   }; \
   const char *name::Names[24] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23, #item24 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum25(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23, item24, item25\
					 ) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23, item24, item25\
			 \
       }; \
       static const unsigned Count = 25u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum25(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23, item24, item25\
					) \
   const name::Type name::Values[25] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22, 23, 24 \
   }; \
   const char *name::Names[25] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23, #item24, #item25\
		 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum26(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23, item24, item25, \
					 item26) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23, item24, item25, \
			item26 \
       }; \
       static const unsigned Count = 26u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum26(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23, item24, item25, \
					item26) \
   const name::Type name::Values[26] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22, 23, 24, 25 \
   }; \
   const char *name::Names[26] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23, #item24, #item25, \
		#item26 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum27(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23, item24, item25, \
					 item26, item27) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23, item24, item25, \
			item26, item27 \
       }; \
       static const unsigned Count = 27u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum27(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23, item24, item25, \
					item26, item27) \
   const name::Type name::Values[27] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22, 23, 24, 25, 26 \
   }; \
   const char *name::Names[27] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23, #item24, #item25, \
		#item26, #item27 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum28(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23, item24, item25, \
					 item26, item27, item28) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23, item24, item25, \
			item26, item27, item28 \
       }; \
       static const unsigned Count = 28u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum28(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23, item24, item25, \
					item26, item27, item28) \
   const name::Type name::Values[28] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22, 23, 24, 25, 26, 27 \
   }; \
   const char *name::Names[28] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23, #item24, #item25, \
		#item26, #item27, #item28 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum29(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23, item24, item25, \
					 item26, item27, item28, item29) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23, item24, item25, \
			item26, item27, item28, item29 \
       }; \
       static const unsigned Count = 29u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum29(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23, item24, item25, \
					item26, item27, item28, item29) \
   const name::Type name::Values[29] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22, 23, 24, 25, 26, 27, 28 \
   }; \
   const char *name::Names[29] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23, #item24, #item25, \
		#item26, #item27, #item28, #item29 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum30(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23, item24, item25, \
					 item26, item27, item28, item29, item30\
					 ) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23, item24, item25, \
			item26, item27, item28, item29, item30\
			 \
       }; \
       static const unsigned Count = 30u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum30(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23, item24, item25, \
					item26, item27, item28, item29, item30\
					) \
   const name::Type name::Values[30] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29\
		 \
   }; \
   const char *name::Names[30] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23, #item24, #item25, \
		#item26, #item27, #item28, #item29, #item30\
		 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


#define DeclareEnum31(name, item1, item2, item3, item4, item5, \
					 item6, item7, item8, item9, item10, \
					 item11, item12, item13, item14, item15, \
					 item16, item17, item18, item19, item20, \
					 item21, item22, item23, item24, item25, \
					 item26, item27, item28, item29, item30, \
					 item31) \
   struct name { \
       ReflectType(name); \
       typedef unsigned Type; \
       enum Enum { \
			item1, item2, item3, item4, item5, \
			item6, item7, item8, item9, item10, \
			item11, item12, item13, item14, item15, \
			item16, item17, item18, item19, item20, \
			item21, item22, item23, item24, item25, \
			item26, item27, item28, item29, item30, \
			item31 \
       }; \
       static const unsigned Count = 31u; \
       static const Type Values[]; \
       static const char *Names[]; \
       name() = default; \
       name(const name &other) = default; \
       name(unsigned value) : value(value) {} \
       operator unsigned() const { return value; } \
       name &operator=(const name &other) { value = other.value; return *this; } \
private: \
       unsigned value; \
   }

#define DefineEnum31(name, item1, item2, item3, item4, item5, \
					item6, item7, item8, item9, item10, \
					item11, item12, item13, item14, item15, \
					item16, item17, item18, item19, item20, \
					item21, item22, item23, item24, item25, \
					item26, item27, item28, item29, item30, \
					item31) \
   const name::Type name::Values[31] = { \
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29, \
		30 \
   }; \
   const char *name::Names[31] = { \
		#item1, #item2, #item3, #item4, #item5, \
		#item6, #item7, #item8, #item9, #item10, \
		#item11, #item12, #item13, #item14, #item15, \
		#item16, #item17, #item18, #item19, #item20, \
		#item21, #item22, #item23, #item24, #item25, \
		#item26, #item27, #item28, #item29, #item30, \
		#item31 \
   }; \
   void name::InitializeMeta(Meta::TypeBuilder &builder) { \
       builder.AddReadOnlyField("Count", &name::Count); \
       builder.AddReadOnlyField("Names", &Names); \
       builder.AddReadOnlyField("Values", &Values); \
   } \


