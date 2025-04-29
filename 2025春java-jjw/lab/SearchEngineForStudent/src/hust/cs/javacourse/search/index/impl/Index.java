package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.*;

import java.io.*;
import java.util.*;

/**
 * AbstractIndex的具体实现类
 */
public class Index extends AbstractIndex {
    /**
     * 返回索引的字符串表示
     *
     * @return 索引的字符串表示
     */
    @Override
    public String toString() {
        StringBuffer sb = new StringBuffer();
        sb.append("docIdToDocPathMapping:\n");
        for(Map.Entry<Integer, String> entry: docIdToDocPathMapping.entrySet()){
            sb.append("\t"+entry.getKey() + "  -->  " + entry.getValue() + "\n");
        }
        sb.append("termToPostingListMapping:\n");
        for(Map.Entry<AbstractTerm, AbstractPostingList> entry: termToPostingListMapping.entrySet()){
            sb.append("\t"+entry.getKey() + "  -->  " + entry.getValue() + "\n");
        }

        return sb.toString();
    }

    /**
     * 添加文档到索引，更新索引内部的HashMap
     *
     * @param document ：文档的AbstractDocument子类型表示
     */
    @Override
    public void addDocument(AbstractDocument document) {
        docIdToDocPathMapping.put(document.getDocId(), document.getDocPath());

        List<AbstractTermTuple> tuples = document.getTuples();
        // tuples.sort((a,b)->{return a.term.getContent().compareTo(b.term.getContent());});

        // 汇总位置
        HashMap<AbstractTerm, List<Integer>> termToPosArrMap = new HashMap<>();
        List<Integer> posArr = new ArrayList<>();
        for (AbstractTermTuple tuple : tuples) {
            posArr = termToPosArrMap.get(tuple.term);
            if (posArr == null) {
                posArr = new ArrayList<>();
            }
            posArr.add(tuple.curPos);
            termToPosArrMap.put(tuple.term, posArr);
        }

        // 添加
        termToPosArrMap.forEach((term, posArrList) -> {
            AbstractPostingList postingList = termToPostingListMapping.get(term);
            if (postingList == null) {
                postingList = new PostingList();
                termToPostingListMapping.put(term, postingList);
            }
            postingList.add(new Posting(document.getDocId(), posArrList.size(), posArrList));
        });
    }

    /**
     * <pre>
     * 从索引文件里加载已经构建好的索引.内部调用FileSerializable接口方法readObject即可
     * @param file ：索引文件
     * </pre>
     */
    @Override
    public void load(File file) {
        ObjectInputStream ois = null;
        try {
            ois = new ObjectInputStream(new FileInputStream(file));
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.readObject(ois);
    }

    /**
     * <pre>
     * 将在内存里构建好的索引写入到文件. 内部调用FileSerializable接口方法writeObject即可
     * @param file ：写入的目标索引文件
     * </pre>
     */
    @Override
    public void save(File file) {
        ObjectOutputStream oos = null;
        try {
            oos = new ObjectOutputStream (new FileOutputStream(file));
        } catch (IOException e) {
            e.printStackTrace();
        }

        this.writeObject(oos);
    }

    /**
     * 返回指定单词的PostingList
     *
     * @param term : 指定的单词
     * @return ：指定单词的PostingList;如果索引字典没有该单词，则返回null
     */
    @Override
    public AbstractPostingList search(AbstractTerm term) {
        AbstractPostingList postingList = termToPostingListMapping.get(term);
        if (postingList == null) {
            return new PostingList();
        }
        return postingList;
    }

    /**
     * 返回索引的字典.字典为索引里所有单词的并集
     *
     * @return ：索引中Term列表
     */
    @Override
    public Set<AbstractTerm> getDictionary() {
        return termToPostingListMapping.keySet();
    }

    /**
     * <pre>
     * 对索引进行优化，包括：
     *      对索引里每个单词的PostingList按docId从小到大排序
     *      同时对每个Posting里的positions从小到大排序
     * 在内存中把索引构建完后执行该方法
     * </pre>
     */
    @Override
    public void optimize() {
        termToPostingListMapping.forEach((k, v) -> {
            v.sort();
            for (int i = 0; i < v.size(); i++) {
                v.get(i).sort();
            }
        });
    }

    /**
     * 根据docId获得对应文档的完全路径名
     *
     * @param docId ：文档id
     * @return : 对应文档的完全路径名
     */
    @Override
    public String getDocName(int docId) {
        if (docIdToDocPathMapping.containsKey(docId)) {
            return docIdToDocPathMapping.get(docId);
        } else {
            return null;
        }
    }

    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(this.docIdToDocPathMapping);
            out.writeObject(this.termToPostingListMapping);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 从二进制文件读
     *
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        try {
            this.docIdToDocPathMapping = (Map<Integer, String>) in.readObject();
            this.termToPostingListMapping = (Map<AbstractTerm, AbstractPostingList>) in.readObject();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
