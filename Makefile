all:
	mkdir build || true
	cd build; \
		cmake ..; make;
	