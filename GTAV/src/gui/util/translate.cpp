#include "pch.h"
#include "translate.h"

translation::translation() {}

translation::translation(std::string original, bool translate, bool global_register) {
	if (global_register) {
		register_translation();
	}

	m_translate = translate;
	set(original);
}

void translation::reset() {
	set_mapped(m_original);
}

void translation::set(std::string str) {
	m_original = str;
	set_mapped(m_original);
}

void translation::set_mapped(std::string str) {
	m_mapped = str;
}

void translation::set_translate(bool translate) {
	m_translate = translate;
}

void translation::register_translation() {
	//TODO :)
}

std::string translation::get_original() {
	return m_original;
}

std::string translation::get() {
	return m_translate ? m_mapped : m_original;
}

bool translation::has_translation() {
	return m_translate;
}