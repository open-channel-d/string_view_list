#pragma once

#include <ostream>
#include <string_view>
#include <iterator>

class string_view_list {
public:
	struct string_view_node {
		string_view_node(std::string_view);

		std::string_view str;
		string_view_node * next;

		~string_view_node();
	};

	string_view_list();
	string_view_list(std::string_view);
	string_view_list(const string_view_list&);

	bool operator==(const string_view_list&) const;
	bool operator!=(const string_view_list&) const;
	bool operator==(std::string_view) const;
	bool operator!=(std::string_view) const;

	void operator+=(std::string_view);
	void append(std::string_view);
	void operator+=(const string_view_list&);
	void append(const string_view_list&);

	size_t size() const;
	char operator[](size_t) const;
	std::string to_string() const;

	bool starts_with(std::string_view) const;
	bool ends_with(std::string_view) const;
	string_view_list substr(size_t pos = 0, size_t count = std::string_view::npos) const;

	struct iterator {
		iterator(string_view_node* node);

		const char& operator*() const;
		iterator& operator++();

		friend bool operator== (const iterator&, const iterator&);
		friend bool operator!= (const iterator&, const iterator&);
	private:
		string_view_node * node;
		size_t index;
	};

	iterator begin() const;
	iterator end() const;

	~string_view_list();

	friend std::ostream& operator<<(std::ostream&, const string_view_list&);
private:
	string_view_node * _first;
	string_view_node * _last;

	size_t _size;
};

std::ostream& operator<<(std::ostream&, const string_view_list&);
string_view_list operator+(std::string_view, std::string_view);
string_view_list operator+(std::string_view, const string_view_list&);
string_view_list operator+(const string_view_list&, std::string_view);
string_view_list operator+(const string_view_list&, const string_view_list&);