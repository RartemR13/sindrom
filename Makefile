all:
	mkdir build || true
	cd build; \
		cmake ..; make;

clear:
	rm -rf build || true