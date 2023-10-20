void TestF?rGodk?ntString() {
	//-	String()
	String str0;	AssertStrEqual(str0, "");

	//-	String(Sträng sträng)
	String s1("foo"); assert(s1 == "foo");
	String str(s1); assert(str == "foo");
	String s3("bar");  assert(s3 == "bar");

	//-	~String() Kom ihåg destruktorn!
	delete new String("hej");
	//TestDelete();

	//	-	operator =(Sträng sträng)
	str = "hej";
	assert((str = s3) == s3);
	assert((str = str) == s3);	//self assignment

								//Ej samma buffert
	str = "heja"; s3 = str;
	str[0] = 'x'; assert(s3[0] == 'h');
	s3[1] = 'y'; assert(str[1] == 'e');


	String str1("foo"), str2("bar"), str3("hej");
	str3 = str = str1;
	assert(str3 == str);
	assert(str1 == str);

	TestCapacitySetting();

	//No extra realloc
	AssertStrEqual(str1, "foo");
	auto xxx = str1.data();
	str1 = String("huj");
	assert(xxx == str1.data());

	//-	operator==
	//testas överallt!
	{
		String s, r;
		s.push_back(0);
		s.push_back(0);
		s.push_back(0);
		r.push_back(0);
		assert(s != r && !(r == s));
	}

	//- operator!=
	assert(str1 != str);
	assert(!(str1 != str1));
	//-	operator[](size_t i) som indexerar utan range check.
	str = "bar";
	str[-1]; str[1000];	//No error
	assert(str[1] == 'a');
	str[1] = 'y';
	assert(str[1] == 'y');

	const String sc(str);
	assert(sc[1] == 'y');
	assert(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value); //Kolla att det blir en const resultat av indexering

																				 //-	push_back(char c)
	TestPushBack();

	// data
	const char* temp = str.data();
	assert(temp == &str[0]);

	//-	size(), capacity() and reloccation test;
	TestPushBackReallocation();

	cout << String("hej\n");
	cout << "Om det står hej pEföregående rad sEär TestFörGodkänt klar\n";

}
