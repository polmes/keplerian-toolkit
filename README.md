# Keplerian Toolkit

_An open-source_ ...

## Building the C++ Shared Library

```
mkdir build && cd build/
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target all
```

### Installing in a Development Directory

```
cmake .. -DCMAKE_BUILD_TYPE=Release -DEVELOPMENT_INSTALL=ON
cmake --build . --target install
```

### Run the C++ Tests

```
ctest .
```

## Installing the Python Module

```
python -m venv .venv && source .venv/bin/activate
pip install . # or .[dev] for testing dependencies
```

### Using the Python Module

```
>>> import ktk
>>> ktk.(...)
```

### Running the Python Tests

```
pytest
```
