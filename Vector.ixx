export module Vector;

export template <typename Type> class Vector {
public:
    Vector() {
        _size = 0;
        _data = new Type;
        _data_copy = nullptr;
        min_size = 0;
    }

    Vector(size_t count) {
        _size = count;
        _data = new Type[count];
        _data_copy = nullptr;
        min_size = 0;
    }

    Vector(size_t count, const Type &value) {
        create_data(count, value);
        _data_copy = nullptr;
        min_size = 0;
    }

    Vector(const Vector &source) {
        copy(source);
        _data_copy = nullptr;
        min_size = 0;
    }

    template <class InputIterator>
    Vector(InputIterator first, InputIterator last) {
        _size = 1;
        Type *data_copy = new Type[_size];

        for (auto it = first; it != last; it++) {
            delete[] _data;
            _data = new Type[_size];

            for (size_t i = 0; i < _size - 1; i++)
                _data[i] = data_copy[i];
            _data[_size - 1] = *it;

            delete[] data_copy;
            data_copy = new Type[_size];
            for (size_t i = 0; i < _size; i++)
                data_copy[i] = _data[i];

            _size++;
        }

        _size--;
        delete[] data_copy;
        _data_copy = nullptr;
        min_size = 0;
    }

    ~Vector() {
        if (_data != nullptr)
        delete[] _data;
        if (_data_copy != nullptr)
        delete[] _data_copy;
    }

    Type &operator[](size_t position) {
        return _data[position];
    }

    Vector operator=(const Vector &right) {
        return copy(right);
    }

    void assign(size_t count, const Type &value) {
        delete[] _data;
        create_data(count, value);
    }

    Type &at(size_t position) {
        return _data[position];
    }

    Type &back() {
        return _data[_size - 1];
    }

    Type *begin() {
        return _data;
    }

    size_t capacity() {
        return _sizeof(_data) / _sizeof(Type);
    }

    void clear() {
        _size = 0;
        delete_data();
        if (_size < min_size)
            _data = new Type[min_size];
    }

    Type *data() {
        return _data;
    }

    bool empty() {
        return (_size == 0) ? true : false;
    }

    Type *end() {
        return _data + _size - 1;
    }

    Type *erase(size_t position) {
        for (size_t i = position; i < _size - 1; i++)
            _data[i] = _data[i + 1];
        _data[_size - 1] = 0;
        return _data;
    }

    Type *erase(size_t first, size_t last) {
        for (size_t i = first; i < _size - last + first; i++)
            _data[i] = _data[i + last - first];
        for (size_t i = _size - last + first; i < _size; i++)
            _data[i] = 0;
        return _data;
    }

    Type &front() {
        return _data[0];
    }

    Type *insert(size_t position, const Type &value) {
        save_data();
        malloc_data(++_size);
        for (size_t i = 0; i < _size - 1; i++) {
            if (i < position)
                _data[i] = _data_copy[i];
            else if (i == position)
                _data[i] = value;
            else
                _data[i] = _data_copy[i - 1];
        }
        delete_data_copy();
        return data[position];
    }

    void insert(size_t position, size_t count, const Type &value) {
        save_data();
        _size += count;
        malloc_data(_size);
        for (size_t i = 0; i < _size; i++) {
            if (i < position)
                _data[i] = _data_copy[i];
            else if (i >= position and i <= position + count)
                _data[i] = value;
            else
                _data[i] = _data_copy[i - count];
        }
        delete_data_copy();
    }

    size_t max_size() const {
        return _max_size;
    }

    void pop_back() {
        _data[_size - 1] = 0;
    }

    void push_back(const Type &value) {
        save_data();
        malloc_data(++_size);
        for (size_t i = 0; i < _size - 1; i++)
            _data[i] = _data_copy[i];
        _data[_size - 1] = value;
        delete_data_copy();
    }

    void reserve(size_t count) {
        min_size = count;
        if (_size < min_size) {
            save_data();
            _data = new Type[min_size];
            for (size_t i = 0; i < _size; i++)
                _data[i] = _data_copy[i];
            delete[] _data_copy;
            _data_copy = nullptr;
        }
    }

    void resize(size_t new_size) {
        save_data();
        malloc_data(new_size);
        for (size_t i = 0; i < (new_size > _size) ? _size : new_size; i++)
            _data[i] = _data_copy[i];
        delete_data_copy();
    }

    void resize(size_t new_size, Type value) {
        save_data();
        malloc_data(new_size);
        for (size_t i = 0; i < (new_size > _size) ? _size : new_size; i++)
            _data[i] = _data_copy[i];
        for (size_t i = _size; i < new_size; i++)
            _data[i] = value;
        delete_data_copy();
    }

    void shrink_to_fit() {
        min_size = 0;
        if (sizeof(_data) / sizeof(Type) > _size) {
            save_data();
            _data = new Type[_size];
            for (size_t i = 0; i < (min_size > _size) ? _size : min_size; i++)
                _data[i] = _data_copy[i];
            delete[] _data_copy;
            _data_copy = nullptr;
        }
    }

    void size() const {
        return _size;
    }

    void swap(Vector<Type> &right) {
        Vector<Type> temp = right;
        right = *this;
        *this = temp;
    }

private:
    const size_t _max_size = 2305843009213693951;

    Type *_data;
    size_t _size;
    size_t min_size;
    Type *_data_copy;

    Vector copy(const Vector &sourse) {
        delete[] _data;
        _size = sourse._size;
        _data = new Type[_size];
        for (size_t i = 0; i < _size; i++)
            _data[i] = sourse[i];
        return *this;
    }

    void save_data() {
        Type *_data_copy = new Type[_size];
        for (size_t i = 0; i < _size; i++)
            _data_copy[i] = _data[i];
        delete_data();
    }

    void malloc_data(size_t new_size) {
        _data = new Type[(new_size < min_size) ? min_size : new_size];
    }

    void create_data(size_t count, const Type &value) {
        _size = count;
        _data = new Type[_size];
        for (size_t i = 0; i < _size; i++)
            _data[i] = value;
    }

    void delete_data() {
        delete[] _data;
        _data = nullptr;
    }

    void delete_data_copy() {
        delete[] _data_copy;
        _data_copy = nullptr;
    }
};