#include "string_view_list.h"

string_view_list::string_view_node::string_view_node(std::string_view str) : str(str), next(nullptr)
{
}

string_view_list::string_view_list() : _first(nullptr), _last(nullptr), _size(0)
{
}

string_view_list::string_view_list(std::string_view string) : string_view_list()
{
	append(string);
};

string_view_list::string_view_list(const string_view_list& list) : string_view_list()
{
	append(list);
}

string_view_list& string_view_list::operator=(const string_view_list& list) {
	if (_first) {
		delete _first;
	}

	_first = nullptr;
	_last = nullptr;
	_size = 0;

	append(list);

	return *this;
}

bool string_view_list::operator==(const string_view_list& list) const
{
	if (_size != list.size()) {
		return false;
	}

	for (auto it_1 = begin(), it_2 = list.begin(); it_1 != end(); ++it_1, ++it_2) {
		if (*it_1 != *it_2) {
			return false;
		}
	}

	return true;
}

bool string_view_list::operator!=(const string_view_list& list) const
{
	return !(*this == list);
}

bool string_view_list::operator==(std::string_view str) const
{
	if (_size != str.length()) {
		return false;
	}

	size_t i = 0;
	for (const char &ch : *this) {
		if (ch != str[i]) {
			return false;
		}
		++i;
	}

	return true;
}

bool string_view_list::operator!=(std::string_view str) const
{
	return !(*this == str);
}


void string_view_list::append(std::string_view string)
{
	_size += string.length();

	if (!_first) {
		_first = new string_view_node(string);
		_last = _first;
		return;
	}

	_last->next = new string_view_node(string);
	_last = _last->next;
}

void string_view_list::operator+=(std::string_view string)
{
	append(string);
}

void string_view_list::append(const string_view_list& list)
{
	string_view_list::string_view_node * current = list._first;

	while (current) {
		append(current->str);
		current = current->next;
	}

}

void string_view_list::operator+=(const string_view_list& list)
{
	string_view_list copy(list);
	append(copy);
}

std::ostream& operator<<(std::ostream& os, const string_view_list& list)
{
	string_view_list::string_view_node * current = list._first;
	while (current) {
		os << current->str;
		current = current->next;
	}
	return os;
}

std::string string_view_list::to_string() const
{
	std::string res;
	string_view_node * current = _first;
	while (current) {
		res += std::string(current->str);
		current = current->next;
	}
	return res;
}

size_t string_view_list::size() const
{
	return _size;
}

char string_view_list::operator[](size_t i) const
{
	size_t current_len = 0;
	string_view_node * current = _first;

	while (current) {
		if (i < current_len + current->str.length()) {
			return current->str[i - current_len];
		}
		current_len += current->str.length();
		current = current->next;
	}
	throw std::out_of_range("string_view_list index out of range");
}

bool string_view_list::starts_with(std::string_view sv) const
{
	if (_size < sv.length()) {
		return false;
	}

	size_t i = 0;
	for (const char& ch : *this) {
		if (i == sv.length()) {
			break;
		}
		if (ch != sv[i]) {
			return false;
		}
		++i;
	}

	return true;	
}

bool string_view_list::ends_with(std::string_view sv) const
{
	if (_size < sv.length()) {
		return false;
	}

	for (size_t i = _size, sv_i = sv.length(); sv_i && i; --i, --sv_i) {
		if ((*this)[i - 1] != sv[sv_i - 1]) {
			return false;
		}
	}

	return true;
}

string_view_list string_view_list::substr(size_t pos, size_t count) const
{
	if (pos >= _size || count == 0) {
		return string_view_list();
	}

	size_t current_len = 0;
	string_view_node * current = _first;

	while (current) {
		if (pos < current_len + current->str.length()) {
			break;
		}
		current_len += current->str.length();
		current = current->next;
	}

	size_t str_pos = pos - current_len;
	
	if (count == std::string_view::npos) {
		string_view_list res(current->str.substr(str_pos));
		current = current->next;
		while (current) {
			res += current->str;
			current = current->next;
		}
		return res;
	}

	if (str_pos + count <= current->str.length() || !current->next) {
		return string_view_list(current->str.substr(str_pos, count));
	}

	string_view_list res(current->str.substr(str_pos));
	size_t substr_len = current->str.length() - str_pos;
	current = current->next;

	while (current) {
		if (substr_len + current->str.length() >= count) {
			res += current->str.substr(0, count - substr_len);
			return res;
		}
		res += current->str;
		substr_len += current->str.length();
		current = current->next;
	}

	return res;
}

string_view_list::iterator string_view_list::begin() const {
	return string_view_list::iterator(_first);
}

string_view_list::iterator string_view_list::end() const {
	return string_view_list::iterator(nullptr);
}

string_view_list::string_view_node::~string_view_node()
{
	if (next) {
		delete next;
	}
}


string_view_list::~string_view_list()
{
	if (_first) {
		delete _first;
	}
}


string_view_list::iterator::iterator(string_view_node* node) : node(node), index(0)
{
}

const char& string_view_list::iterator::operator*() const
{
	return node->str[index];
}

string_view_list::iterator& string_view_list::iterator::operator++()
{
	if (index != node->str.length() - 1) {
		++index;
	}
	else {
		node = node->next;
		index = 0;
	}
	return *this;
}

bool operator== (const string_view_list::iterator& a, const string_view_list::iterator& b)
{ 
	return a.node == b.node && a.index == b.index;
}

bool operator!= (const string_view_list::iterator& a, const string_view_list::iterator& b)
{ 
	return a.node != b.node || a.index != b.index;
}


string_view_list operator+(std::string_view _first, std::string_view second)
{
	string_view_list result(_first);
	result += second;
	return result;
}

string_view_list operator+(const string_view_list& list, std::string_view str)
{
	string_view_list res(list);
	res += str;
	return res;
}

string_view_list operator+(std::string_view str_view, const string_view_list& list)
{
	string_view_list res(str_view);
	res += list;
	return res;
}

string_view_list operator+(const string_view_list& list_1, const string_view_list& list_2)
{
	string_view_list res(list_1);
	res += list_2;
	return res;
}
