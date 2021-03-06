#pragma once
template <typename K, typename V>
class Entry {						// a (key, value) pair
public:						// public functions

	typedef K Key;					// key type
	typedef V Value;
  
	Entry(const K& k = K(), const V& v = V())		// constructor
		: _key(k), _value(v) { }
	const K& key() const { return _key; }		// get key
	const V& value() const { return _value; }		// get value
	void setKey(const K& k) { _key = k; }		// set key
	void setValue(const V& v) { _value = v; }		// set value
	bool operator==(const Entry e) const { return _key == e.key() && _value == e.value(); };
	void operator=(const Entry e) { setKey(e.key()); setValue(e.value()); };
private:						// private data
	K _key;						// key
	V _value;						// value
};