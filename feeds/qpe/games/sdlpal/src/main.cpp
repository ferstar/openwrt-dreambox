#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>


#include <qtopia/qpeapplication.h>
#include <qtopia/qcopenvelope_qws.h>


static char message[]="bad child signal?";
#define MAXLINE 20

/*
*
* running the extern command !
*
*/
void RunProgram(void)
{
//	::chdir("/opt/paladin");
//	::setenv("PWD", "/opt/paladin", 1);
//	::system("/usr/bin/filebrowser");
	::system("/usr/bin/paladin");
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



int main(void)
{

	pid_t pid;
	pid_t ppid;
	int pipe_1[2];
	int pipe_fd[2];

	ppid = ::getppid();

	::signal(SIGCHLD, SIG_IGN);

	::signal(SIGTERM, SIG_DFL);
	::signal(SIGKILL, SIG_DFL);

	if ( ::pipe(pipe_1) < 0) {
		perror("pipe");
		exit(1);
	}

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
//		fprintf(stderr, "# Child !\n");
		orphan_process(); //孤儿进程，让孙子进程脱离关系，运行

/* 下面是孙子进程在运行！ */

		/* 1 发送信号，让qpe停止运行STOP */
//		::kill(ppid, SIGTERM); //::kill(ppid+7, SIGTERM);::kill(ppid+8, SIGTERM);
//		::kill(ppid, SIGKILL); //::kill(ppid+7, SIGKILL );::kill(ppid+8, SIGKILL );

		int t, end;
		end = ::getpid() - 2;
		for(t=ppid; t<end; t++){
			::kill(t, SIGTERM);
			::kill(t, SIGKILL);
		}
		//QCopEnvelope e("QPE/System", "shutdown()" ); //不起作用!

		/* x 发送信号，给parent parent，让其等待qpe进入STOP后再运行 */
		::close(pipe_1[0]); //关闭接收端
		::write(pipe_1[1], message, sizeof(message));

		/* 2 调用外部程序 */
		RunProgram();

		/* 3 发送信号，让qpe运行 */

		/* 4 发送信号，给parent parent，让程序退出 */
		::close(pipe_fd[0]); //关闭接收端
		::write(pipe_fd[1], message, sizeof(message));
		sleep(1);

		::close(pipe_1[1]);//结束退出
		::close(pipe_fd[1]);

		/* 5 重启qpe */
		execl( (QPEApplication::qpeDir()+"bin/qpe").latin1(), "qpe", 0 );
//		QCopEnvelope e("QPE/System", "restart()" ); //因为qpe已经被关闭了，所以无法响应restart！
		exit(1); //if here , it is error !

/***************父进程*******************/
	} else {       /* parent */
//		fprintf(stderr, "# Parent !\n");

		/* 1 等待孙子进程的信号，同步！等待qpe进入STOP后再运行 */
		int n;
		char line[MAXLINE];

		::close(pipe_1[1]);//关闭发送端
		n = ::read(pipe_1[0], line, MAXLINE);

		fprintf(stderr, "%s\n", line);
		if ( ! ::strcmp(message, line) ) { //比较接收的是否正确，正确则输出ok
			fprintf(stderr, "ok !\n");
		}

		/* 2 等待孙子进程的信号，同步！让程序退出 */
		::close(pipe_fd[1]);//关闭发送端
		n = ::read(pipe_fd[0], line, MAXLINE);

		fprintf(stderr, "%s\n", line);
		if ( ! ::strcmp(message, line) ) { //比较接收的是否正确，正确则输出ok
			fprintf(stderr, "ok !\n");
		}

		/* 3 等待子进程，实际上没用，主要考pipe进行同步 */
		waitpid(pid, 0, 0);
		exit(0);
	}
	return 0;
}

