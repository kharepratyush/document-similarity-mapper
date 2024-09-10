## document-similarity-mapper


A C++ code to sort the documents depending on their similarity with query document.
- Each document (docName.txt) contains english words separated by spaces.
- Similarity between two documents is the cosine distance between the respective word vectors.

Executable Details :

Executable takes two arguments
- Arg1 : path of folder that contains documents to be indexed
- Arg2 : path of document for which I want to find similar documents

Source Code Output:

Names of top 3 retreived documents in descending order of their similarity score.

Details :

- Creates an inverted index of all documents in the index folder
- Cosine Similarity : http://en.wikipedia.org/wiki/Cosine_similarity 
