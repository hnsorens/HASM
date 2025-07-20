all:
	gcc -Wall -Wextra -Werror -pedantic -g main.c assembler.c Instructions.c InstructionHandlers.c -o HASM

test: all
	@total_tests=0; \
	passed_tests=0; \
	inputs=Tests/Code/*; \
	expected_folder="Tests/Bin"; \
	for input in $$inputs; do \
		total_tests=$$((total_tests + 1)); \
		base_name=$$(basename "$$input"); \
		base_name="$${base_name%.*}"; \
		expected="$$expected_folder/$$base_name"; \
		actual="OUTPUT"; \
		./HASM "$$input" -o OUTPUT; \
		if diff -q "$$actual" "$$expected" > /dev/null; then \
			echo "Test $$total_tests ($$base_name): PASSED"; \
			passed_tests=$$((passed_tests + 1)); \
		else \
			echo "Test $$total_tests ($$base_name): FAILED"; \
			echo "Differences:"; \
			diff "$$actual" "$$expected"; \
		fi; \
	done; \
	echo; \
	echo "Total tests: $$total_tests"; \
	echo "Passed tests: $$passed_tests"

clean:
	rm -f HASM OUTPUT 