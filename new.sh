nextID=$(( $(find . -maxdepth 1 -type d -name 'hw*' | wc -l) + 1 ))
echo "Create hw${nextID}..."
mkdir hw${nextID} hw${nextID}/code hw${nextID}/doc
cp dep/Makefile hw${nextID}/code

