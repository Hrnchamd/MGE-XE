#include "ipc/vecwrap.h"
#include "support/log.h"

#include <algorithm>

// ----------------------
// StlVector
// ----------------------
StlVector::StlVector() : m_vector(), m_it(m_vector.begin()), m_end(m_vector.end()) {}
StlVector::StlVector(std::vector<const RenderMesh*>&& vector) : m_vector(vector), m_it(m_vector.begin()), m_end(m_vector.end()) {}

StlVector& StlVector::operator=(const StlVector& other) {
	m_vector = other.m_vector;
	m_it = other.m_it;
	m_end = other.m_end;
	return *this;
}

void StlVector::restart() {
	m_it = m_vector.begin();
	m_end = m_vector.end();
}

const RenderMesh& StlVector::first() {
	return *m_vector.front();
}

const RenderMesh& StlVector::next() {
	auto& elem = **m_it;
	++m_it;
	return elem;
}

void StlVector::start_write() {}

void StlVector::start_read() {}

bool StlVector::push_back(const RenderMesh& value) {
	m_vector.push_back(&value);
	return true;
}

bool StlVector::end_write() {
	return true;
}

void StlVector::end_read() {}

bool StlVector::at_end() {
	return m_it == m_end;
}

std::uint32_t StlVector::size() const {
	return static_cast<std::uint32_t>(m_vector.size());
}

bool StlVector::reserve(std::uint32_t count) {
	m_vector.reserve(count);
	return true;
}

void StlVector::clear() {
	m_vector.clear();
}

void StlVector::truncate(std::uint32_t count) {
	if (m_vector.size() > count) {
		m_vector.resize(count);
	}
}

void StlVector::sort_by_state() {
	if (m_vector.size() > 0) {
		std::sort(m_vector.begin(), m_vector.end(), [](const RenderMesh* lhs, const RenderMesh* rhs) {
			return QuadTreeMesh::CompareByState(*lhs, *rhs);
		});
	}
}

void StlVector::sort_by_texture() {
	if (m_vector.size() > 0) {
		std::sort(m_vector.begin(), m_vector.end(), [](const RenderMesh* lhs, const RenderMesh* rhs) {
			return QuadTreeMesh::CompareByTexture(*lhs, *rhs);
		});
	}
}

std::vector<const RenderMesh*>::iterator StlVector::begin() {
	return m_vector.begin();
}

std::vector<const RenderMesh*>::iterator StlVector::end() {
	return m_vector.end();
}


// ----------------------
// IpcClientVector
// ----------------------
IpcClientVector::IpcClientVector() : m_view(), m_isAtBeginning(true) {}
IpcClientVector::IpcClientVector(const IPC::VecView<RenderMesh>& view) : m_view(view), m_isAtBeginning(true) {
	restart();
}
IpcClientVector::IpcClientVector(IPC::VecView<RenderMesh>&& view) : m_view(view), m_isAtBeginning(true) {
	restart();
}

IpcClientVector& IpcClientVector::operator=(const IpcClientVector& other) {
	m_view = other.m_view;
	m_isAtBeginning = other.m_isAtBeginning;
	return *this;
}

void IpcClientVector::restart() {
	m_view.set_index(0);
	m_isAtBeginning = true;
}

const RenderMesh& IpcClientVector::first() {
	m_isAtBeginning = true;
	return m_view.front();
}

const RenderMesh& IpcClientVector::next() {
	// the server vector iterator gets a pointer to the current element, increments the iterator,
	// and then returns the pointer to the original element. but we can't do that here because if
	// the current element is the last element in the window, then incrementing the iterator will
	// cause the window to be re-mapped, and our pointer will no longer point to the element we
	// wanted. so we have to always return a pointer to the current element, not a past/future
	// element.
	if (m_isAtBeginning) {
		m_isAtBeginning = false;
		return m_view.front();
	} else {
		return *++m_view;
	}
}

void IpcClientVector::start_write() {
	m_view.start_write();
}

void IpcClientVector::start_read() {
	m_view.start_read();
}

bool IpcClientVector::push_back(const RenderMesh& value) {
	return m_view.push_back(value);
}

bool IpcClientVector::end_write() {
	return m_view.end_write();
}

void IpcClientVector::end_read() {
	m_view.end_read();
}

bool IpcClientVector::at_end() {
	return m_view.at_end();
}

std::uint32_t IpcClientVector::size() const {
	return m_view.size();
}

bool IpcClientVector::reserve(std::uint32_t count) {
	return m_view.reserve(count);
}

void IpcClientVector::clear() {
	m_view.clear();
}

void IpcClientVector::truncate(std::uint32_t count) {
	m_view.truncate(count);
}

IPC::VecView<RenderMesh> IpcClientVector::begin() {
	return m_view.begin();
}

IPC::VecView<RenderMesh> IpcClientVector::end() {
	return m_view.end();
}


// ----------------------
// IpcServerVector
// ----------------------
IpcServerVector::IpcServerVector(IPC::Vec<RenderMesh>& view) : m_vec(view), m_it(m_vec.begin()) {
	restart();
}

IpcServerVector& IpcServerVector::operator=(const IpcServerVector& other) {
	m_vec = other.m_vec;
	m_it = m_vec.begin();
	return *this;
}

void IpcServerVector::restart() {
	m_it = m_vec.begin();
}

const RenderMesh& IpcServerVector::first() {
	return m_vec.front();
}

const RenderMesh& IpcServerVector::next() {
	auto& elem = *m_it;
	++m_it;
	return elem;
}

void IpcServerVector::start_write() {
	m_vec.start_write();
}

void IpcServerVector::start_read() {
	m_vec.start_read();
}

bool IpcServerVector::push_back(const RenderMesh& value) {
	return m_vec.push_back(value);
}

bool IpcServerVector::end_write() {
	return m_vec.end_write();
}

void IpcServerVector::end_read() {
	m_vec.end_read();
}

bool IpcServerVector::at_end() {
	return m_it.at_end();
}

std::uint32_t IpcServerVector::size() const {
	return m_vec.size();
}

bool IpcServerVector::reserve(std::uint32_t count) {
	return m_vec.reserve(count);
}

void IpcServerVector::clear() {
	m_vec.clear();
}

void IpcServerVector::truncate(std::uint32_t count) {
	m_vec.truncate(count);
}

void IpcServerVector::sort_by_state() {
	if (m_vec.size() > 0) {
		std::sort(m_vec.begin(), m_vec.end(), QuadTreeMesh::CompareByState);
	}
}

void IpcServerVector::sort_by_texture() {
	if (m_vec.size() > 0) {
		std::sort(m_vec.begin(), m_vec.end(), QuadTreeMesh::CompareByTexture);
	}
}

IPC::Vec<RenderMesh>::iterator IpcServerVector::begin() {
	return m_vec.begin();
}

IPC::Vec<RenderMesh>::iterator IpcServerVector::end() {
	return m_vec.end();
}