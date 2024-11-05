# FastCask-DB

FastCask-DB is a naive implementation of [Bitcask paper](https://riak.com/assets/bitcask-intro.pdf) in pure C++.

## Getting Started
- Clone the repository using the following command
```
git clone https://github.com/helios2003/FastCask-DB.git
```
- Change directory into the cloned folder and insert the following commands
```
 ./run.sh
```
- You will enter the terminal for FastCask DB where you can type the commands
- Press ``Ctrl + C`` for a forceful closure or type ``EXIT`` for a graceful closure.
- Run ``make clean`` to remove the object files created.

## Performance testing
- The performance has been measured using [Catch2](https://github.com/catchorg/Catch2). Follow the installation steps as given [here](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top).
- After downloading and configuring Catch2 write the following command
```
cd benchmark
./test.sh
``` 
## List of Commands Implemented
- ``SET <key> <value> <expiry_time: optional>``: Sets the key and corresponding value with an optional expiry time.
- ``GET <key>``: Gets the value associated with the key.
- ``DELETE <key>``: Deletes the key and the associated values
- ``LIST``: Lists all the keys.
- ``SYNC``: Restores the database if there was a forceful exit done earlier (i.e. will not work if you exited from the DB shell using the ``EXIT`` command).
- ``EXIT``: Graceful closure deleting all the data stored in memory and on the disk.