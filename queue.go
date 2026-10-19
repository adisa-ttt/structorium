package main

type QNode struct {
	Data string
	Next *QNode
}

type Queue struct {
	Head *QNode
	Tail *QNode
}

func NewQueue() *Queue {
	return &Queue{}
}

func (q *Queue) Empty() bool {
	return q.Head == nil
}

func (q *Queue) Push(str string) {
	node := &QNode{Data: str}
	if q.Tail == nil {
		q.Head = node
		q.Tail = node
	} else {
		q.Tail.Next = node
		q.Tail = node
	}
}

func (q *Queue) Pop() (string, bool) {
	if q.Empty() {
		return "", false
	}
	out := q.Head.Data
	q.Head = q.Head.Next
	if q.Head == nil {
		q.Tail = nil
	}
	return out, true
}

func (q *Queue) Get() []string {
	var result []string
	curr := q.Head
	for curr != nil {
		result = append(result, curr.Data)
		curr = curr.Next
	}
	return result
}

func (q *Queue) Clear() {
	q.Head = nil
	q.Tail = nil
}


/*
./structorium_go --file test.data --query 'SPUSH mystack item2'
./structorium_go --file test.data --query 'SGET mystack'
./structorium_go --file test.data --query 'TINSERT mytree 10'
./structorium_go --file test.data --query 'TINSERT mytree 5'
./structorium_go --file test.data --query 'TINSERT mytree 20'
./structorium_go --file test.data --query 'TGET mytree'
./structorium_go --file test.data --query 'ISMEMBER mytree 5'
./structorium_go --file test.data --query 'MPUSH myarr hello'
./structorium_go --file test.data --query 'MPUSH myarr 0 world'
./structorium_go --file test.data --query 'MGET myarr'
./structorium_go --file test.data --query 'PRINT mytree'

./structorium_go --file test.data --query 'FPUSH mylist back A'
./structorium_go --file test.data --query 'FPUSH mylist back B'
./structorium_go --file test.data --query 'FPUSH mylist front C'
./structorium_go --file test.data --query 'FGET mylist'
./structorium_go --file test.data --query 'FPUSH mylist before B X'
./structorium_go --file test.data --query 'FPUSH mylist after A Y'
./structorium_go --file test.data --query 'FGET mylist'
./structorium_go --file test.data --query 'FDEL mylist X'
./structorium_go --file test.data --query 'FGET mylist'
./structorium_go --file test.data --query 'FPOP mylist front'
./structorium_go --file test.data --query 'FPOP mylist back'

./structorium_go --file test.data --query 'LPUSH mydll back 1'
./structorium_go --file test.data --query 'LPUSH mydll back 2'
./structorium_go --file test.data --query 'LPUSH mydll front 0'
./structorium_go --file test.data --query 'LGET mydll'
./structorium_go --file test.data --query 'LPUSH mydll before 2 99'
./structorium_go --file test.data --query 'LGET mydll'
./structorium_go --file test.data --query 'LDEL mydll 99'
./structorium_go --file test.data --query 'LGET mydll'
./structorium_go --file test.data --query 'LPOP mydll back'

./structorium_go --file test.data --query 'QPUSH myqueue first'
./structorium_go --file test.data --query 'QPUSH myqueue second'
./structorium_go --file test.data --query 'QPUSH myqueue third'
./structorium_go --file test.data --query 'QGET myqueue'
./structorium_go --file test.data --query 'QPOP myqueue'
./structorium_go --file test.data --query 'QGET myqueue'*/