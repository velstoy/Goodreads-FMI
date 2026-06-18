# Goodreads Console Application

A C++20 console application simulating the Goodreads platform, developed as an Object-Oriented Programming course project (FMI 2025-2026).

## Features
* **Roles:** Reader, Author, and Publisher with distinct permissions and capabilities.
* **Social:** Follow users, add mutual friends, and receive automated inbox notifications for new book releases and job offers.
* **Library:** Manage custom shelves, add books to your profile, rate them, and track your reading status (e.g., currently reading, dropped).
* **Publishing:** Publishers can send job offers to Authors and officially publish new books to the platform.
* **Search:** Case-insensitive fuzzy search that allows up to 2 typos when looking for users and books.
* **Persistence:** All system data (users, books, shelves, messages) is automatically serialized to a local binary file upon exit and restored on startup.

## Command Reference
Type `help` in the application at any time to see the commands available to your current role.

### General Commands
* `register <user> <pass> <reader|author|publisher>` - Create a new account.
* `login <user> <pass>` - Log into an existing account.
* `logout` - Log out of the current session.
* `exit` - Save all data and shut down the application.

### Reader Commands
* `search <name>` - Find users and books.
* `profile [reader]` - View user stats, favorite books, and shelves.
* `add-book <book> <status> [rating]` - Add a book to your profile.
* `delete-book <book>` - Remove a book from your profile completely.
* `create-shelf <name>` / `delete-shelf <name>` - Manage your custom shelves.
* `add-to-shelf <book> <shelf>` / `remove-from-shelf <book> <shelf>` - Organize books on your shelves.
* `show-shelf [reader] <name>` - View books on a specific shelf (viewing others requires being mutual friends).
* `follow <user>` - Follow a user and send them a notification.
* `friends [reader]` - View mutual followers.
* `show-inbox [filter]` - View your messages (optional filter: `friends`).
* `read-msg <index>` / `delete-msg <index>` - Manage your inbox.
* `add-birthday [date]` - Set or remove your birthday.

### Author Commands *(Inherits all Reader commands)*
* `accept-offer <index>` - Accept a job offer from a publisher.
* `leave <publisher>` - End a working partnership with a publisher.
* `followers` - List all users following you.
* `show-inbox [filter]` - Can be filtered specifically for `offers`.

### Publisher Commands *(Inherits General commands)*
* `offer <author>` - Send a job offer to an author.
* `publish <title> <author> <date> <pages> <genres...>` - Publish a new book and notify all relevant followers.
* `add-synopsis <title> <synopsis>` - Set or update a published book's summary.