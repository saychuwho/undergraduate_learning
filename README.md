# UNDERGRATUATE LEARNING

이 리포지토리는 학부 과목 프로젝트 코드를 정리해놓은 곳입니다. 

---

This repository is place for my undergraduate codes. There are undergraduate subject assignments.

## Table

- [UNDERGRATUATE LEARNING](#undergratuate-learning)
  - [Table](#table)
  - [What's in here](#whats-in-here)
  - [Object-Oriented Programming](#object-oriented-programming)
  - [System Programming](#system-programming)
  - [Computer Architecture](#computer-architecture)
  - [Reinforcement Learning](#reinforcement-learning)
  - [Introduction to Machine Learning](#introduction-to-machine-learning)
  - [Operating System](#operating-system)
  - [Computer Algorithm](#computer-algorithm)

## What's in here

DGIST Computer Science 학부 과목 프로젝트 코드들이 있습니다.

경고 : 남의 코드를 그대로 베끼는 거는 표절입니다. 당신이 DGIST 학부생이라면, 표절은 절대로 해서는 안됩니다. 제 코드에서 아이디어를 얻는 거는 상관없으나, 여러분의 과제는 여러분 스스로 하셔야 합니다. 이 과제를 베껴서 제출했을 시 불이익은 여러분이 지셔야 합니다. 

- 과목 목록
  - 객체 지향 프로그래밍
  - 시스템 프로그래밍
  - 컴퓨터구조
  - 기계학습개론
  - 운영체제
  - 컴퓨터 알고리즘

---
assignment code from DGIST computer science subject

WARNING : DO NOT COPY THE EXACT CODE WHEN YOU ARE DGIST UNDERGRADUATE STUDENT. IT IS ILLEGAL TO COPY SOMEONES COMPLETE CODE. PLAGIARISM IS STRICTLY CAUGHT AND YOU WILL PAY THE PRICE.

- Subject List
  - Object-Oriented Programming
  - System Programming
  - Computer Architecture
  - Introduction to Machine Learning
  - Operating System
  - Computer Algorithm


## Object-Oriented Programming

"ATM 기기 만들기" 팀 프로젝트 코드입니다. / 블로그 설명 / [code](/Object_Oriented_Programming/final_source_code.cpp)

저는 대략적인 클래스 구조와, Atm 기계의 session 부분을 작성했습니다.

---

Team project code make ATM machine using C++

## System Programming

라즈베리 파이 OS에서 구동되는 파일 압축 프로그램입니다. / 블로그 설명 / [code](/System_Programming/main.c)

---

Make file compression program running on Raspberry Pi. Code is aimed to run on Raspberry Pi OS.

## Computer Architecture

네 개의 프로젝트가 있습니다. 모든 코드는 C++로 작성되었습니다. Ubuntu 20.04, g++ 9.4.0 환경에서 제작했습니다

- [Project 1](/Computer_Architecture/project1/) / [report](/Computer_Architecture/project1/project1_report.pdf) / [블로그 설명](https://velog.io/@saychuwho/Project-1-%EA%B0%84%EB%8B%A8%ED%95%9C-MIPS-Assembler) : 간단한 MIPS 어셈블러
- [Project 2](/Computer_Architecture/project2/) / [report](/Computer_Architecture/project2/project2_report.pdf) / [블로그 설명](https://velog.io/@saychuwho/Project-1-%EA%B0%84%EB%8B%A8%ED%95%9C-MIPS-Assembler) : MIPS Instruction Emulator
- [Project 3](/Computer_Architecture/project3/) / [report](/Computer_Architecture/project3/Project3_report.pdf) / 블로그 설명 : MIPS single pipeline CPU
- [Project 4](/Computer_Architecture/project4/) / [report](/Computer_Architecture/project4/report_project4.pdf) / [report(English)](/Computer_Architecture/project4/report_project4_english.pdf) / 블로그 설명 : L1, L2 Cache와 벤치마크

---

There are four assignment. All codes written in C++, aimed to run on Ubuntu 20.04.

- project 1 : make simple MIPS Assembler
- project 2 : make MIPS Instruction Emulator (might not work properly)
- project 3 : make single pipeline CPU can run MIPS Instructions
- project 4 : make cache and test with benchmark files. 

## Reinforcement Learning

강화학습 팀 프로젝트는 제 다른 리포지토리인 [saychuwho/TStarBot1](https://github.com/saychuwho/TStarBot1)에 있습니다. 자세한 팀 프로젝트 내용은 [final report](https://github.com/saychuwho/TStarBot1/blob/dev-open/RL_team_project_final_report_2.pdf)와 [final presentation](https://github.com/saychuwho/TStarBot1/blob/dev-open/RL_team_project_2_final_presentation.pdf)에 자세히 설명되어 있습니다.

## Introduction to Machine Learning

다음 코드들이 jupyter notebook 형태로 있습니다

- linear regression practice: [code](/Introduction_To_Machine_Learning/assignment1.ipynb)
- supervised learning practice using scikit-learn: [Logistic regression](/Introduction_To_Machine_Learning/assignment2_code_LogisticRegression.ipynb) / [KNN](/Introduction_To_Machine_Learning/assignment2_code_KNN.ipynb) / [Random forest](/Introduction_To_Machine_Learning/assignment2_code_RandomForest.ipynb) / [SVM](/Introduction_To_Machine_Learning/assignment2_code_SVM.ipynb) / [Gradient Boosting](/Introduction_To_Machine_Learning/assignment2_code_GradientBoosting.ipynb)
- unsupervised learning practice using scikit-learn: [Question 1](/Introduction_To_Machine_Learning/assignment3_question1.ipynb) / [Question 2](/Introduction_To_Machine_Learning/assignment3_question2_8.ipynb)
- collaborative filtering 실습: [code](/Introduction_To_Machine_Learning/assignment4_part-1-item-item-recommender.ipynb)

## Operating System

모든 코드들은 [DGIST datalab/xv6](https://github.com/dgist-datalab/xv6)에 있는 수정된 xv6에서 돌아갑니다. 각 프로젝트 별 branch가 있어 해당 branch xv6에서만 동작합니다. 코드들은 .patch 형태로 올렸습니다. 또한, [별도의 repository](https://github.com/saychuwho/DGIST_OS_projects_xv6/)에 동작 가능한 형태로 코드를 업데이트 해뒀습니다.

- How to run code
  - 모든 코드들은 Ubuntu 20.04에서 실행 가능합니다.
  - 다음 명령어를 이용해 xv6를 부팅할 수 있습니다. `make clean; make qemu-nox -j`
  - 각 프로젝트를 구현한 branch가 다르니, `git checkout`을 이용해 각 프로젝트에 맞는 branch로 들어가야 합니다.

- Project 1 / branch: miniprj-2023 / [report](/Operating_Systems/project1_report.pdf) / 블로그 설명 / [code](https://github.com/saychuwho/DGIST_OS_projects_xv6/tree/miniprj-2023) : CFS 스케쥴러와 프로세스 우선 순위 조정 system call / EEVDF 스케쥴러 (둘 다 linux 커널 2.6.23에 있는 [rbtree.c](https://github.com/torvalds/linux/blob/v2.6.23/lib/rbtree.c), [rbtree.h](https://github.com/torvalds/linux/blob/v2.6.23/include/linux/rbtree.h)가 필요하다.)
- Project 2 / branch: inverted / [report](/Operating_Systems/project2_report.pdf) / 블로그 설명 / [code](https://github.com/saychuwho/DGIST_OS_projects_xv6/tree/inverted) : Inverted page table (모든 usertest를 통과하지는 못했지만, 부팅은 한다.)
- Project 3 / branch: raid / [report](/Operating_Systems/project3_report.pdf) / 블로그 설명 / [code](https://github.com/saychuwho/DGIST_OS_projects_xv6/tree/raid) : RAID 5 (disk block cache 양이 많이 필요하다)

---

All codes works on modified xv6 x86 version which is in [DGIST datalab](https://github.com/dgist-datalab/xv6). Every project have proper branches. Project code is in .patch form.

- project 1 : CFS scheduler + process priority change system call / EEVDF scheduler (rbtree.c, rbtree.h from linux 2.6.23 is needed)
- project 2 : inverted page table (not work properly since this doesn't pass all usertests, but it boots)
- project 3 : RAID 5 (it requires lots of disk block cache)

## Computer Algorithm

다음 알고리즘 문제들 solution이 있다

- Project 3: 그래프 알고리즘, 다이나믹 프로그래밍 / 블로그 설명 / [Problems](/Computer_Algorithm/HW3.pdf) / [1](/Computer_Algorithm/project3_1.py) / [2](/Computer_Algorithm/project3_2.py) / [3](/Computer_Algorithm/project3_3.py) / [4](/Computer_Algorithm/project3_4.py) / [5](/Computer_Algorithm/project3_5.py)
- Project 4: 그리디 알고리즘, min-cut max-flow theorem / 블로그 설명 / [Problems](/Computer_Algorithm/HW4.pdf) / [1](/Computer_Algorithm/project4_1.py) / [2](/Computer_Algorithm/project4_2.py) / [3](/Computer_Algorithm/project4_3.py) / [4](/Computer_Algorithm/project4_4.py) / [5](/Computer_Algorithm/project4_5.py)

---

project 3, project 4 answer code is uploaded with problems

- project 3 : graph algorithm, dynamic programming
- project 4 : greedy algorithm, min-cut max-flow theorem