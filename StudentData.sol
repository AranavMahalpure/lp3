// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData {
    struct Student {
        uint id;
        string name;
        uint age;
        string class;
    }

    Student[] public students;

    event StudentAdded(uint id, string name, uint age, string class);

    function addStudent(uint _id, string memory _name, uint _age, string memory _class) public {
        students.push(Student(_id, _name, _age, _class));
        emit StudentAdded(_id, _name, _age, _class);
    }

    function getStudent(uint index) public view returns(uint, string memory, uint, string memory) {
        require(index < students.length, "Student index out of bounds.");
        Student memory student = students[index];
        return (student.id, student.name, student.age, student.class);
    }

    function getStudentCount() public view returns(uint) {
        return students.length;
    }

    fallback() external payable {
        revert("This contract does not accept Ether.");
    }

    receive() external payable {
        revert("This contract does not accept direct Ether transfers.");
    }
}
