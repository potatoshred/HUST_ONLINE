package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.util.FileUtil;

import java.io.File;
import java.util.List;

public class IndexBuilder extends AbstractIndexBuilder {
    public IndexBuilder(AbstractDocumentBuilder docBuilder) {
        super(docBuilder);
    }

    @Override
    public AbstractIndex buildIndex(String rootDirectory) {

        AbstractIndex index = new Index();

        List<String> filePaths = FileUtil.list(rootDirectory, "txt");
        for(int i = 0; i < filePaths.size(); i++) {
            File file = new File(filePaths.get(i));
            index.addDocument(this.docBuilder.build(i, filePaths.get(i), file));
        }

        return index;
    }
}
