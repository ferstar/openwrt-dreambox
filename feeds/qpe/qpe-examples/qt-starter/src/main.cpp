//在BSP自带的qtopia可以运行，QWS_DISPLAY=:1
//而自己编译的qtopia则不行

#include <qpushbutton.h>
#include <qtopia/qpeapplication.h>
#include <qfont.h>
#include <qtimer.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/*
*
* running the extern command !
*
*/
void RunProgram(void)
{
	::system("ls --color=auto");
	::system("filebrowser-test");
	::sleep(30);
}


/*
* to creat a orphan process
*/
pid_t orphan_process(void)
{
	pid_t pid;

	if( (pid= ::fork()) > 0) exit(EXIT_SUCCESS);//是父进程，结束父进程
	else if(pid< 0)
		exit(EXIT_FAILURE);//fork失败，退出

	//是子进程
	::setsid();//子进程成为新的会话组长和进程组长

	return pid;
}


int main(int argc, char **argv)
{

	pid_t pid;
	pid_t ppid;
	int pipe_fd[2];

	ppid = ::getppid();

	::signal(SIGSTOP, SIG_DFL);
	::signal(SIGCONT, SIG_DFL);
	::signal(SIGCHLD, SIG_IGN);

	if ( ::pipe(pipe_fd) < 0) {
		perror("pipe");
		exit(1);
	}

	if ((pid = ::fork()) < 0) {
		perror("fork");
		exit(1);
	}

/***************子进程*******************/
	if (pid == 0) { /* child */
		fprintf(stderr, "# Child !\n");
		orphan_process(); //孤儿进程，让孙子进程脱离关系，运行

/************** 下面是孙子进程在运行！ **************/
		char line[20]={0};

		/* 接收信号，等待父进程的qtopia apps退出后才让QPE stoped */
		::close(pipe_fd[1]);//关闭发送端
		::read(pipe_fd[0], line, 7);
		fprintf(stderr, "READ #: %s\n", line);
		sleep(1);

		/* stop QPE */
		::kill(ppid, SIGSTOP);
		/* 运行外部程序 */
		RunProgram();
		/* continue QPE */
		::kill(ppid, SIGCONT);

		fprintf(stderr, "Child exit now !\n");
		::close(pipe_fd[0]);
		exit(0);

/***************父进程*******************/
	} else {       /* parent */
		fprintf(stderr, "# Parent !\n");

		int ret;
		QPEApplication a( argc, argv );
		QTimer::singleShot(20, &a, SLOT(quit()));
		ret = a.exec();
/************************************************/
		fprintf(stderr, "TEST # after QPEApplication::exec() \n");

		/* 发送信号 */
		::close(pipe_fd[0]); //关闭接收端
		::write(pipe_fd[1], "message", sizeof("message"));
		::close(pipe_fd[1]);//结束退出

		fprintf(stderr, "TEST # exit Qtopia apps\n");

		return ret;
	}

}
