ID=$(shell cd ..;basename "$$PWD")
OutputPath=$(shell mkdir -p ../../dsa15_042/$(ID);cd ../../dsa15_042/$(ID);pwd)
Files=$(wildcard **) $(wildcard **/*)

push:
	-@rm -rf $(OutputPath) 2>/dev/null
	@cp -r ../code $(OutputPath)
	@echo -e "Target Folder:" '\t' $(OutputPath)
	@echo "@" $(shell date +"%T  [%m-%d]")
	@echo "--- File(s) and Folder(s) ---"
	@for f in $(Files); do \
	    echo $$f; \
	done

