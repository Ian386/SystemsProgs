#!/bin/bash

# Step 1: Create a new directory named TestDir
mkdir -p TestDir

# Step 2: Navigate to TestDir
cd TestDir

# Step 3: Create the script file test.sh and write the content
echo '#!/bin/bash' > test.sh
echo 'echo "Script executed successfully"' >> test.sh

# Step 4: Add executable permissions to test.sh
chmod +x test.sh

# Step 5: Run the script to verify it works
./test.sh
