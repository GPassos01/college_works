/*		DDL		*/
DROP SCHEMA  if exists projetobdgrupo1;
CREATE SCHEMA projetobdgrupo1;
USE projetobdgrupo1;

CREATE TABLE `pessoa` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(45) NOT NULL,
  `endereco` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
);
CREATE TABLE `pessoafisica` (
  `idPessoaFisica` int(11) NOT NULL,
  `cpf` varchar(15) NOT NULL,
  `rg` varchar(15) NOT NULL,
  `salario` float DEFAULT NULL,
  `matricula` varchar(45) NOT NULL,
  `nomeSocial` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idPessoaFisica`),
  UNIQUE KEY `cpf_UNIQUE` (`cpf`),
  UNIQUE KEY `rg_UNIQUE` (`rg`),
  UNIQUE KEY `matricula_UNIQUE` (`matricula`),
  CONSTRAINT `idPessoa8` FOREIGN KEY (`idPessoaFisica`) REFERENCES `pessoa` (`id`)
);
CREATE TABLE `afastamento` (
  `idAfastamento` int(11) NOT NULL AUTO_INCREMENT,
  `dataInicio` date NOT NULL,
  `dataFim` date NOT NULL,
  `idPessoaFisica` int(11) NOT NULL,
  PRIMARY KEY (`idAfastamento`),
  KEY `idPessoaFisica_idx` (`idPessoaFisica`),
  CONSTRAINT `idPessoaFisica` FOREIGN KEY (`idPessoaFisica`) REFERENCES `pessoafisica` (`idPessoaFisica`)
);

CREATE TABLE `pessoajuridica` (
  `idPessoaJuridica` int(11) NOT NULL,
  `CNPJ` varchar(20) NOT NULL,
  `iE` varchar(15) NOT NULL,
  `fantasia` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idPessoaJuridica`),
  CONSTRAINT `idPessoa9` FOREIGN KEY (`idPessoaJuridica`) REFERENCES `pessoa` (`id`)
);

CREATE TABLE `departamento` (
  `idDepartamento` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(45) NOT NULL,
  `idChefe` int(11) NOT NULL,
  `idPessoaJuridica` int(11) NOT NULL,
  PRIMARY KEY (`idDepartamento`),
  KEY `idChefe_idx` (`idChefe`),
  KEY `idPessoaJuridica_idx` (`idPessoaJuridica`),
  CONSTRAINT `idChefe` FOREIGN KEY (`idChefe`) REFERENCES `pessoafisica` (`idPessoaFisica`),
  CONSTRAINT `idPessoaJuridica2` FOREIGN KEY (`idPessoaJuridica`) REFERENCES `pessoajuridica` (`idPessoaJuridica`)
);

CREATE TABLE `curso` (
  `idCurso` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(45) NOT NULL,
  `area` varchar(45) NOT NULL,
  `duracao` int(11) NOT NULL,
  `periodo` varchar(45) NOT NULL,
  `cargaHoraria` int(11) NOT NULL,
  `idDepartamento` int(11) NOT NULL,
  `idPessoaJuridica` int(11) NOT NULL,
  PRIMARY KEY (`idCurso`),
  KEY `idDepartamento_idx` (`idDepartamento`),
  KEY `idPessoa_idx` (`idPessoaJuridica`),
  CONSTRAINT `idDepartamento` FOREIGN KEY (`idDepartamento`) REFERENCES `departamento` (`idDepartamento`),
  CONSTRAINT `idPessoaJuridica` FOREIGN KEY (`idPessoaJuridica`) REFERENCES `pessoajuridica` (`idPessoaJuridica`)
);

CREATE TABLE `disciplina` (
  `idDisciplina` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(45) NOT NULL,
  `cargaHoraria` int(11) DEFAULT NULL,
  PRIMARY KEY (`idDisciplina`)
);

CREATE TABLE `coordenador` (
  `idCoordenador` int(11) NOT NULL AUTO_INCREMENT,
  `dataInicio` date NOT NULL,
  `dataFim` date DEFAULT NULL,
  `idCurso` int(11) NOT NULL,
  PRIMARY KEY (`idCoordenador`),
  KEY `idCurso_idx` (`idCurso`),
  CONSTRAINT `idCurso` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `idPessoaFisica2` FOREIGN KEY (`idCoordenador`) REFERENCES `pessoafisica` (`idPessoaFisica`)
);
CREATE TABLE `tiposala` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(45) NOT NULL,
  PRIMARY KEY (`id`)
);
CREATE TABLE `sala` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idPessoaJuridica` int(11) NOT NULL,
  `idTipoSala` int(11) NOT NULL,
  `bloco` varchar(45) NOT NULL,
  `numero` int(11) NOT NULL,
  `capacidade` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `tipoSala_idx` (`idTipoSala`),
  KEY `idPessoaJuridica4` (`idPessoaJuridica`),
  CONSTRAINT `idPessoaJuridica7` FOREIGN KEY (`idPessoaJuridica`) REFERENCES `pessoajuridica` (`idPessoaJuridica`),
  CONSTRAINT `tipoSala` FOREIGN KEY (`idTipoSala`) REFERENCES `tiposala` (`id`)
);
CREATE TABLE `curso_disc` (
  `idCurso` int(11) NOT NULL,
  `idDisciplina` int(11) NOT NULL,
  PRIMARY KEY (`idCurso`,`idDisciplina`),
  KEY `idDisciplina_idx` (`idDisciplina`),
  CONSTRAINT `idCurso2` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `idDisciplina2` FOREIGN KEY (`idDisciplina`) REFERENCES `disciplina` (`idDisciplina`)
);

CREATE TABLE `disc_tiposala` (
  `idDisc` int(11) NOT NULL,
  `idTipoSala` int(11) NOT NULL,
  PRIMARY KEY (`idDisc`,`idTipoSala`),
  KEY `idTipoSala_idx` (`idTipoSala`),
  CONSTRAINT `idDisciplina3` FOREIGN KEY (`idDisc`) REFERENCES `disciplina` (`idDisciplina`),
  CONSTRAINT `idTipoSala` FOREIGN KEY (`idTipoSala`) REFERENCES `tiposala` (`id`)
);

CREATE TABLE `equivalencia` (
  `idDisciplina` int(11) NOT NULL,
  `idEquivalencia` int(11) NOT NULL,
  PRIMARY KEY (`idDisciplina`,`idEquivalencia`),
  KEY `idEquivalencia_idx` (`idEquivalencia`),
  CONSTRAINT `idDisciplina4` FOREIGN KEY (`idDisciplina`) REFERENCES `disciplina` (`idDisciplina`),
  CONSTRAINT `idEquivalencia` FOREIGN KEY (`idEquivalencia`) REFERENCES `disciplina` (`idDisciplina`)
);
CREATE TABLE `faixa_hora` (
  `idFaixaHora` int(11) NOT NULL AUTO_INCREMENT,
  `idPessoaFisica` int(11) NOT NULL,
  `diaSemana` int(11) NOT NULL,
  `inicio` time NOT NULL,
  `fim` time NOT NULL,
  PRIMARY KEY (`idFaixaHora`),
  UNIQUE KEY `idPessoa_UNIQUE` (`idPessoaFisica`),
  CONSTRAINT `idPessoa3` FOREIGN KEY (`idPessoaFisica`) REFERENCES `pessoafisica` (`idPessoaFisica`)
);
CREATE TABLE `feriado` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(45) NOT NULL,
  `dataInicio` date NOT NULL,
  `dataFim` date NOT NULL,
  PRIMARY KEY (`id`)
);
CREATE TABLE `inst_curso` (
  `idPessoa` int(11) NOT NULL,
  `idCurso` int(11) NOT NULL,
  PRIMARY KEY (`idPessoa`,`idCurso`),
  KEY `idCurso3_idx` (`idCurso`),
  CONSTRAINT `idCurso3` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `idPessoaJuridica4` FOREIGN KEY (`idPessoa`) REFERENCES `pessoajuridica` (`idPessoaJuridica`)
);
CREATE TABLE `instituicao` (
  `idInstituicao` int(11) NOT NULL,
  PRIMARY KEY (`idInstituicao`),
  CONSTRAINT `idPessoaJuridica6` FOREIGN KEY (`idInstituicao`) REFERENCES `pessoajuridica` (`idPessoaJuridica`)
);
CREATE TABLE `prerequisito` (
  `idDisciplina` int(11) NOT NULL,
  `idPreReq` int(11) NOT NULL,
  PRIMARY KEY (`idDisciplina`,`idPreReq`),
  KEY `idDisciplina6_idx` (`idPreReq`),
  CONSTRAINT `idDisciplina6` FOREIGN KEY (`idDisciplina`) REFERENCES `disciplina` (`idDisciplina`),
  CONSTRAINT `idPreReq` FOREIGN KEY (`idPreReq`) REFERENCES `disciplina` (`idDisciplina`)
);
CREATE TABLE `professor` (
  `idProfessor` int(11) NOT NULL,
  `formacao` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idProfessor`),
  CONSTRAINT `idPessoaFisica6` FOREIGN KEY (`idProfessor`) REFERENCES `pessoafisica` (`idPessoaFisica`)
);
CREATE TABLE `prof_depto` (
  `idProfessor` int(11) NOT NULL,
  `idDepartamento` int(11) NOT NULL,
  PRIMARY KEY (`idProfessor`,`idDepartamento`),
  KEY `idDepartamento_idx` (`idDepartamento`),
  CONSTRAINT `idDepartamento2` FOREIGN KEY (`idDepartamento`) REFERENCES `departamento` (`idDepartamento`),
  CONSTRAINT `idProfessor` FOREIGN KEY (`idProfessor`) REFERENCES `professor` (`idProfessor`)
);
CREATE TABLE `prof_disc_esp` (
  `idProfessor` int(11) NOT NULL,
  `idDisciplina` int(11) NOT NULL,
  PRIMARY KEY (`idProfessor`,`idDisciplina`),
  KEY `idDisciplina_idx` (`idDisciplina`),
  CONSTRAINT `idDisciplina` FOREIGN KEY (`idDisciplina`) REFERENCES `disciplina` (`idDisciplina`),
  CONSTRAINT `idProfessor2` FOREIGN KEY (`idProfessor`) REFERENCES `professor` (`idProfessor`)
);

CREATE TABLE `prof_disc_minis` (
  `idProfessor` int(11) NOT NULL,
  `idDisciplina` int(11) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `ano` int(11) NOT NULL,
  `semestre` int(11) NOT NULL,
  PRIMARY KEY (`idProfessor`,`idDisciplina`),
  KEY `idDisciplina2_idx` (`idDisciplina`),
  KEY `idCurso_idx` (`idCurso`),
  CONSTRAINT `idCurso4` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `idDisciplina5` FOREIGN KEY (`idDisciplina`) REFERENCES `disciplina` (`idDisciplina`),
  CONSTRAINT `idProfessor3` FOREIGN KEY (`idProfessor`) REFERENCES `professor` (`idProfessor`)
);
CREATE TABLE `secretario` (
  `idSecretario` int(11) NOT NULL,
  `horarioEntrada` float DEFAULT NULL,
  `horarioSaida` float DEFAULT NULL,
  PRIMARY KEY (`idSecretario`),
  CONSTRAINT `idPessoaFisica5` FOREIGN KEY (`idSecretario`) REFERENCES `pessoafisica` (`idPessoaFisica`)
);

create table calendario (
	ano int,
	semestre int,
	disciplina int,
	diasemana int,
	horainicio time,
	horafinal time
);

/**/

/* PROCEDURES */


DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_afastamento`(in codigo int, in dataInicioIn date, in dataFimIn date, in nomePessoa varchar(45))
BEGIN
    declare codigoPessoa int default 0;
    select id into codigoPessoa from pessoa where Pessoa.nome = nomePessoa;
   	 
    if (codigo is null && codigoPessoa !=0) then
   	 insert into afastamento (idAfastamento,dataInicio,dataFim, idPessoaFisica) values (codigo,dataInicioIn,dataFimIn, codigoPessoa);
    elseif (codigo>0 && (codigoPessoa = 0 || dataInicioIn is null || dataFimIn is null)) then
   	 delete from afastamento where codigo = idAfastamento;
	else
   	 update afastamento set dataInicio = dataInicioIn, dataFim = dataFimIn, idPessoaFisica = codigoPessoa where idAfastamento = codigo;
	end if;
END ;;
DELIMITER ;

DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_coordenador`(in nomePessoa varchar(45), in dataInicioIn date, in dataFimIn date, in nomeCurso varchar(45))
BEGIN	
    declare codigoPessoa int default 0;
    declare codigoCurso int default 0;
    
    select id into codigoPessoa from pessoa inner join pessoafisica on pessoa.id = pessoafisica.idPessoaFisica inner join professor on  pessoafisica.idPessoaFisica = professor.idProfessor where pessoa.nome = nomePessoa;
    select idCurso into codigoCurso from curso where Curso.nome = nomeCurso;
    
    if (codigoPessoa!= 0 && codigoCurso !=0) then
		insert into coordenador(idCoordenador,dataInicio,dataFim, idCurso) values (codigoPessoa,dataInicioIn,dataFimIn, codigoCurso);
    elseif (codigoPessoa>0 && (codigoCurso =0 || dataInicioIn is null || dataFimIn is null)) then
		delete from coordenador where codigoPessoa = idCoordenador;
	else
		update coordenador set dataInicio = dataInicioIn, dataFim = dataFimIn, idCurso = codigoCurso where idCoordenador = codigoPessoa;
	end if;
END ;;
DELIMITER ;

DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_curso`(in codigo int, in nomeIn varchar(45), in areaIn varchar(45), in duracaoIn int, in periodoIn varchar(45), in cargaHorariaIn int,in nomeDepartamento varchar(45) , in nomePessoaJuridica varchar(45))
BEGIN
    declare codigoDepartamento int default 0;
    declare codigoPessoa int default 0;
    
    select idDepartamento into codigoDepartamento from departamento where Departamento.nome = nomeDepartamento;
    select id into codigoPessoa from pessoa where Pessoa.nome = nomePessoaJuridica;

    
    if (codigo is null && codigoDepartamento !=0  && codigoPessoa != 0) then
   	 insert into curso(idCurso,nome,area, duracao, periodo, cargaHoraria, idDepartamento, idPessoaJuridica) values (codigo,nomeIn,areaIn, duracaoIn, periodoIn, cargaHorariaIn, codigoDepartamento, codigoPessoa);
    elseif (codigo>0 && (nomeIn is null || areaIn is null || duracaoIn is null || periodoIn is null || cargaHorariaIn is null || codigoDepartamento = 0  || codigoPessoa = 0)) then
   	 delete from curso where codigo = idCurso;
	else
   	 update curso set nome = nomeIn, area = areaIn, duracao = duracaoin, periodo = periodoIn, cargaHoraria = cargaHorariaIn, idDepartamento = codigoDepartamento, idPessoaJuridica = codigoPessoa where idCurso = codigo;
	end if;    
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_curso_disc`(in nomeCurso varchar(45), in nomeDisciplina varchar(45))
BEGIN    
    declare codigoCurso int default 0;
	declare codigoDisciplina int default 0;
    
    select idCurso into codigoCurso from curso where Curso.nome = nomeCurso;
	select idDisciplina into codigoDisciplina from disciplina where Disciplina.nome = nomeDisciplina;
    
    if (codigoCurso != 0 && codigoDisciplina != 0 ) then
   	 insert into curso_disc(idCurso, idDisciplina) values (codigoCurso,codigoDisciplina);
    elseif (codigoCurso > 0 && codigoDisciplina >0) then
   	 delete from curso_disc where ((codigoCurso = idCurso ) && (codigoDisciplina = idDisciplina));
	else
   	 update curso_disc set idCurso = codigoCurso, idDisciplina = codigoDisciplina where idCurso = codigoCurso && idDisciplina = codigoDisciplina;
	end if;    
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_departamento`(in codigo int,in nomeIn varchar(45), in nomeChefe varchar(45), in nomePessoaJuridica varchar(45))
BEGIN
    declare codigoChefe int default 0;
    declare codigoPessoaJuridica int default 0;
    
    select id into codigoChefe from pessoa where Pessoa.nome = nomeChefe;
    select id into codigoPessoaJuridica from pessoa where Pessoa.nome = nomePessoaJuridica;
    
    if (codigo is null &&  codigoChefe != 0  && codigoPessoaJuridica != 0) then
   	 insert into departamento(idDepartamento,nome,idChefe, idPessoaJuridica) values (codigo,nomeIn, codigoChefe, codigoPessoaJuridica);
    elseif (codigo>0 && (nomeIn is null || codigoChefe = 0  || codigoPessoaJuridica = 0)) then
   	 delete from departamento where codigo = idDepartamento;
	else
   	 update departamento set nome = nomeIn,idChefe= codigoChefe, idPessoaJuridica = codigoPessoaJuridica where idDepartamento = codigo;
	end if;    
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_disc_tiposala`(in nomeDisciplina varchar(45), in nomeTipoSala varchar(45))
BEGIN
	declare codigoDisciplina int default 0;
    declare codigoTipoSala int default 0;
    
    select idDisciplina into codigoDisciplina from disciplina where Disciplina.nome = nomeDisciplina;
    select id into codigoTipoSala from tiposala where Tiposala.nome = nomeTipoSala;

    
    if (codigoDisciplina != 0 && codigoTipoSala != 0 ) then
		insert into disc_tiposala(idDisc, idTipoSala) values (codigoDisciplina,codigoTipoSala);
    elseif (codigoDisciplina > 0 && codigoTipoSala >0) then
		delete from disc_tiposala where ((codigoDisciplina = idDisc ) && (codigoTipoSala = idTipoSala));
	else
		update disc_tiposala set idDisc = codigoDisciplina, idTipoSala = codigoTipoSala where idDisc = codigoDisciplina && idTipoSala = codigoTipoSala;
	end if;     
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_disciplina`(in codigo int , in nomeIn varchar (45), in cargaHorariaIn int)
BEGIN
  if (codigo is null) then
   	 insert into disciplina (idDisciplina, nome,cargaHoraria) values (codigo,nomeIn,cargaHorariaIn);
    elseif (codigo>0 && (nomeIn is null || cargaHorariaIn is null)) then
   	 delete from disciplina where codigo = idDisciplina;
	else
   	 update disciplina set nome = nomeIn, cargaHoraria = cargaHorariaIn where idDisciplina= codigo;
	end if;
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_equivalencia`(in nomeDisciplina varchar(45), in nomeEquivalencia varchar (45))
BEGIN
    declare codigoDisciplina int default 0;
	declare codigoEquivalencia int default 0;
    
    select idDisciplina into codigoDisciplina from disciplina where Disciplina.nome = nomeDisciplina;
	select idDisciplina into codigoEquivalencia from disciplina where Disciplina.nome = nomeEquivalencia;
    
    if (codigoDisciplina != 0 && codigoEquivalencia != 0 ) then
   	 insert into equivalencia(idDisciplina, idEquivalencia) values (codigoDisciplina, codigoEquivalencia);
    elseif (codigoDisciplina > 0 && codigoEquivalencia >0) then
   	 delete from equivalencia where ((codigoDisciplina = idDisciplina ) && (codigoEquivalencia = idEquivalencia));
	else
   	 update equivalencia set idDisciplina = codigoDisciplina, idEquivalencia = codigoEquivalencia where idDisciplina= codigoDisciplina && idEquivalencia = codigoEquivalencia;
	end if;    
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_faixa_hora`(in codigo int, in nomePessoa varchar(45), in diaSemanaIn int, in  inicioIn time, in fimIn time)
BEGIN
    declare codigoPessoa int default 0;
    select id into codigoPessoa from pessoa where Pessoa.nome = nomePessoa;
   	 
    if (codigo is null && codigoPessoa != 0 ) then
   	 insert into faixa_hora (idFaixaHora,idPessoaFisica,diaSemana, inicio, fim) values (codigo,codigoPessoa,diaSemanaIn,inicioIn,fimIn );
    elseif (codigo>0 && (codigoPessoa = 0 || diaSemanaIn is null || inicioIn is null || fimIn is null)) then
   	 delete from faixa_hora where codigo = idFaixaHora;
	else
   	 update faixa_hora set idPessoaFisica = codigoPessoa, diaSemana = diaSemanaIn, inicio = inicioIn,fim = fimIn where idFaixaHora = codigo;
	end if;
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_feriado`(in codigo int, in nomeIn varchar(45), in dataInicioIn date, in dataFimIn date)
BEGIN
 if (codigo is null) then
   	 insert into feriado (id, nome,dataInicio, dataFim) values (codigo,nomeIn,dataInicioIn, dataFimIn);
    elseif (codigo>0 && (nomeIn is null || dataInicioIn is null || dataFimIn is null)) then
   	 delete from feriado where codigo = id;
	else
   	 update feriado set nome = nomeIn, dataInicio = dataInicioIn , dataFim = dataFimIn where id =  codigo;
	end if;
END ;;
DELIMITER ;


DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_inst_curso`(in nomePessoa varchar(45), in nomeCurso varchar (45))
BEGIN
    declare codigoPessoa int default 0;
	declare codigoCurso  int default 0;
    
    select id into codigoPessoa from pessoa where Pessoa.nome = nomePessoa;
	select idCurso into codigoCurso from curso where Curso.nome = nomeCurso;
    
    if (codigoPessoa != 0 && codigoCurso != 0 ) then
   	 insert into inst_curso(idPessoa, idCurso) values (codigoPessoa, codigoCurso);
    elseif (codigoPessoa > 0 && codigoCurso >0) then
   	 delete from inst_curso where ((codigoPessoa = idPessoa ) && (codigoCurso = idCurso));
	else
   	 update inst_curso set idPessoa = codigoPessoa, idCurso = codigoCurso where idPessoa= codigoPessoa && idCurso = codigoCurso;
	end if;    
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_instituicao`(in codigoInstituicao int)
BEGIN
    if(codigoInstituicao !=0) then
   	 insert into instituicao (idInstituicao) values (codigoInstituicao);
    elseif (codigoInstituicao > 0 ) then
   	 delete from instituicao where codigoInstituicao = idInstituicao;
    end if;
END ;;
DELIMITER ;

DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_pessoa`(inout codigo int, in nomeIn varchar(45), in enderecoIn varchar(45))
BEGIN
	declare codigoPessoa int default 0;
    if (codigo is null) then
   	 insert into pessoa (id,nome,endereco) values (codigo,nomeIn,enderecoIn);
     select id into codigoPessoa from pessoa where nome = nomeIn;
    elseif (codigo>0 && (nomeIn is null || enderecoIn is null)) then
   	 delete from pessoa where codigo = id;
	else
   	 update pessoa set nome = nomeIn, endereco = enderecoIn where id= codigo;
	end if;
    set codigo = codigoPessoa;
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_pessoafisica`(in codigoPessoa int,in cpfIn varchar(15), in rgIn varchar(15), in salarioIn float, in matriculaIn varchar(45), in nomeSocialIn varchar(45) )
BEGIN
    if (codigoPessoa !=0) then
		insert into pessoafisica (idPessoaFisica,cpf,rg, salario, matricula, nomeSocial) values (codigoPessoa,cpfIn,rgIn,salarioIn,matriculaIn,nomeSocialIn);
    elseif (codigoPessoa > 0 && (cpfIn is null || rgIn is null|| salarioIn is null|| matriculaIn is null|| nomeSocialIn is null)) then
		delete from pesssoafisica where codigoPessoa = idPessoaFisica;
	else
		update pessoafisica set cpf = cpfIn, rg = rgIn , salario = salarioIn, matricula = matriculaIn, nomeSocial = nomeSocialIn where idPessoaFisica= codigoPessoa;
	end if;
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_pessoajuridica`(in codigoPessoa  int, in CNPJIn varchar(20), in iEIn varchar(15), in fantasiaIn varchar(45))
BEGIN
    if (codigoPessoa !=0) then
   	 insert into pessoajuridica(idPessoaJuridica,CNPJ,iE, fantasia) values (codigoPessoa,CNPJIn,iEIn,fantasiaIn);
    elseif (codigoPessoa > 0 && ( CNPJIn is null || iEIn is null|| fantasiaIn is null)) then
   	 delete from pesssoajuridica where codigoPessoa = idPessoaJuridica;
	else
   	 update pesssoajuridica set CNPJ = CNPJIn, iE = iEIn , fantasia = fantasiaIn where idPessoaJuridica= codigoPessoa;
	end if;
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_prerequisito`(in nomeDisciplina varchar(45), in nomePreRequisito varchar(45))
BEGIN
    declare codigoDisciplina int default 0;
	declare codigoPreRequisito int default 0;
    
    select idDisciplina into codigoDisciplina from disciplina where Disciplina.nome = nomeDisciplina;
	select idDisciplina into codigoPrerequisito from disciplina where Disciplina.nome = nomePreRequisito;
    
    if (codigoDisciplina != 0 && codigoPrerequisito != 0 ) then
   	 insert into prerequisito(idDisciplina, idPreReq) values (codigoDisciplina,codigoPrerequisito);
    elseif (codigoDisciplina > 0 && codigoPrerequisito >0) then
   	 delete from prerequisito where ((codigoDisciplina = idDisciplina ) && (codigoPrerequisito = idPreReq));
	else
   	 update prerequisito set idDisciplina = codigoDisciplina, idPreReq = codigoPreRequisito where idDisciplina = codigoDisciplina && idPreReq = codigoPreRequisito;
	end if;   
END ;;
DELIMITER ;

DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_prof_depto`(in nomeProfessor varchar(45) , in nomeDepartamento varchar(45))
BEGIN
    declare codigoProfessor int default 0;
	declare codigoDepartamento int default 0;
    
    select id into codigoProfessor from pessoa where Pessoa.nome = nomeProfessor;
	select idDepartamento  into codigoDepartamento from departamento where Departamento.nome = nomeDepartamento;
    
    if (codigoProfessor != 0 && codigoDepartamento != 0 ) then
   	 insert into prof_depto(idProfessor, idDepartamento) values (codigoProfessor,codigoDepartamento);
    elseif (codigoProfessor > 0 && codigoDepartamento >0) then
   	 delete from prof_depto where ((codigoProfessor = idProfessor ) && (codigoDepartamento = idDepartamento));
	else
   	 update prof_depto set idProfessor = codigoProfessor, idDepartamento = codigoDepartamento where idProfessor = codigoProfessor && idDepartamento = codigoDepartamento;
	end if;    
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_prof_disc_esp`(in nomeProfessor varchar(45), in nomeDisciplina varchar(45))
BEGIN
    declare codigoProfessor int default 0;
	declare codigoDisciplina int default 0;
    
    select id into codigoProfessor from pessoa where Pessoa.nome = nomeProfessor;
	select idDisciplina  into codigoDisciplina from disciplina where Disciplina.nome = nomeDisciplina;
    
    if (codigoProfessor != 0 && codigoDisciplina != 0 ) then
   	 insert into prof_disc_esp(idProfessor, idDisciplina) values (codigoProfessor,codigoDisciplina);
    elseif (codigoProfessor > 0 && codigoDisciplina >0) then
   	 delete from prof_disc_esp where ((codigoProfessor = idProfessor ) && (codigoDisciplina = idDisciplina));
	else
   	 update prof_disc_esp set idProfessor = codigoProfessor, idDisciplina = codigoDisciplina where idProfessor = codigoProfessor && idDisciplina = codigoDisciplina;
	end if;    
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_prof_disc_minis`(in nomeProfessor varchar(45), in nomeDisciplina varchar(45),in nomeCurso varchar(45), in anoIn int, in semestreIn int)
BEGIN
	declare codigoProfessor int default 0;
	declare codigoDisciplina int default 0;
    declare codigoCurso int default 0;
    
    select id into codigoProfessor from pessoa where Pessoa.nome = nomeProfessor;
	select idDisciplina  into codigoDisciplina from disciplina where Disciplina.nome = nomeDisciplina;
    select idCurso  into codigoCurso from curso where Curso.nome = nomeCurso;
    
    if (codigoProfessor != 0 && codigoDisciplina != 0 ) then
   	 insert into prof_disc_minis(idProfessor, idDisciplina, idCurso, ano,semestre) values (codigoProfessor,codigoDisciplina,codigoCurso, anoIn,semestreIn);
    elseif (codigoProfessor > 0 && codigoDisciplina >0 && (codigoCurso > 0|| anoIn is null || semestreIn is null )) then
   	 delete from prof_disc_minis where ((codigoProfessor = idProfessor ) && (codigoDisciplina = idDisciplina));
	else
   	 update prof_disc_minis set idProfessor = codigoProfessor, idDisciplina = codigoDisciplina, idCurso = codigoCurso, ano = anoIn, semestre = semestreIn where idProfessor = codigoProfessor && idDisciplina = codigoDisciplina;
	end if; 
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_professor`(in codigoProfessor int, in formacaoIn varchar(45))
BEGIN
    if (codigoProfessor !=0) then
   	 insert into professor (idProfessor, formacao) values (codigoProfessor,formacaoIn);
    elseif (codigoProfessor>0 && (formacaoIn is null )) then
   	 delete from professor where codigoProfessor = idProfessor;
	else
   	 update professor set formacao = formacaoIn where idProfessor = codigoProfessor;
	end if;
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_sala`(in codigo int, in nomePessoaJuridica varchar(45), in nomeTipoSala varchar(45), in blocoIn varchar(45), in numeroIn int, in capacidadeIn int)
BEGIN
    declare codigoPessoa int default 0;
     declare codigoTipoSala int default 0;
     
    select id into codigoPessoa from pessoa where Pessoa.nome = nomePessoaJuridica;
    select id into codigoTipoSala from tiposala where TipoSala.nome = nomeTipoSala;
    if (codigo is null && codigoPessoa != 0 && codigoTipoSala !=0 ) then
   	 insert into sala (id, idPessoaJuridica, idTipoSala, bloco, numero, capacidade) values (codigo,codigoPessoa, codigoTipoSala, blocoIn, numeroIn,capacidadeIn);
    elseif (codigo>0 && (codigoPessoa = 0 || codigoTipoSala = 0 || blocoIn is null|| numeroin is null|| capacidadeIn is null)) then
   	 delete from sala where codigo = id;
	else
   	 update sala set idPessoaFisica = codigoPessoa, idTipoSala = codigoTipoSala, bloco = blocoIn, numero = numeroIn, capacidade = capacidadeIn where id = codigo;
	end if;
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_secretario`(in codigoSecretario int, in horarioEntradaIn float, in horarioSaidaIn float)
BEGIN
    if (codigoSecretario !=0) then
   	 insert into secretario (idSecretario,horarioEntrada,horarioSaida) values (codigoSecretario,horarioEntradaIn,horarioSaidaIn);
    elseif (codigoSecretario > 0 && (horarioEntradaIn is null || horarioSaidaIn is null)) then
   	 delete from secretario where codigoSecretario = idSecretario;
	else
   	 update secretario set horarioEntrada = horarioEntradaIn, horarioSaida = horarioSaidaIn where idSecretario= codigoSecretario;
	end if;
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `manut_tiposala`(in codigo int, in nomeIn varchar(45))
BEGIN
    if (codigo is null) then
   	 insert into tiposala (id,nome) values (codigo,nomeIn);
    elseif (codigo > 0 && (nomeIn is null)) then
   	 delete from tiposala where id = codigo;
	else
   	 update tiposala set nome = nomeIn where id= codigo;
	end if;
END ;;
DELIMITER ;
DELIMITER ;;

CREATE DEFINER=`root`@`localhost` PROCEDURE `cadastro_secretario`(in codigo int, in nomeIn varchar(45), in enderecoIn varchar(45),in cpfIn varchar(15),
 in rgIn varchar(15), in salarioIn float, in matriculaIn varchar(45), in nomeSocialIn varchar(45),
 in horarioEntradaIn float, in horarioSaidaIn float)
BEGIN
    declare codigoSec int default 0;
	set codigoSec = codigo;
	call manut_pessoa(codigoSec,nomeIn,enderecoIn);
    call manut_pessoafisica(codigoSec, cpfIn,rgIn,salarioIn,matriculaIn,nomeSocialIn);
    call manut_secretario(codigoSec,horarioEntradaIn,horarioSaidaIn);
END ;;
DELIMITER ;

DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `cadastro_professor`(in codigo int, in nomeIn varchar(45), in enderecoIn varchar(45),in cpfIn varchar(15),
 in rgIn varchar(15), in salarioIn float, in matriculaIn varchar(45), in nomeSocialIn varchar(45),
 in formacaoIn varchar(45))
BEGIN
    declare codigoProf int default 0;
	set codigoProf = codigo;
	call manut_pessoa(codigoProf,nomeIn,enderecoIn);
    call manut_pessoafisica(codigoProf, cpfIn,rgIn,salarioIn,matriculaIn,nomeSocialIn);
    call manut_professor(codigoProf,formacaoIn);
END ;;
DELIMITER ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `cadastro_coordenador`(in codigo int, in nomeIn varchar(45), in enderecoIn varchar(45),in cpfIn varchar(15),
 in rgIn varchar(15), in salarioIn float, in matriculaIn varchar(45), in nomeSocialIn varchar(45),
 in formacaoIn varchar(45))
BEGIN
    declare codigoProf int default 0;
	set codigoProf = codigo;
	call manut_pessoa(codigoProf,nomeIn,enderecoIn);
    call manut_pessoafisica(codigoProf, cpfIn,rgIn,salarioIn,matriculaIn,nomeSocialIn);
    call manut_professor(codigoProf,formacaoIn);
END ;;
DELIMITER ;

DELIMITER ;;

CREATE DEFINER=`root`@`localhost` PROCEDURE `cadastro_instituicao`(in codigo int, in cnpjIn varchar(20), in iEIn varchar(15),in fantasiaIn varchar(45),
 in nomeIn varchar(45), in enderecoIn varchar(45))
BEGIN
    declare codigoInstituicao int default 0;
	set codigoInstituicao = codigo;
	call manut_pessoa(codigoInstituicao,nomeIn,enderecoIn);
    call manut_pessoajuridica(codigoInstituicao, cnpjIn,iEIn,fantasiaIn);
    call manut_instituicao(codigoInstituicao);
END ;;
DELIMITER ;

DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `geracalendario`(in p_ano int, in p_semestre int, in p_curso int)
BEGIN
	declare hinicio time default '08:00:00';
    declare hfinal time default '18:00:00';
    declare dinicio time;
    declare dfinal time;
    declare profinicio time default null;
    declare proffim time default null;
    declare profdiasemana int default null;
    declare codigodisciplina int;
    declare qtde int default 0;
    declare contador int default 0;
	DECLARE done BOOL DEFAULT false;
    /* Declaração de uma variável tipo CURSOR para guardar todas as informações dos professores */
    /* a Variável pesquisa apresenta as informações do professor */
     declare pesquisa cursor for select  Disciplina.idDisciplina 
										from disciplina inner join curso_disc on Disciplina.idDisciplina = curso_disc.idDisciplina 
                                        where curso_disc.idCurso = p_curso;
	DECLARE CONTINUE HANDLER 
	FOR NOT FOUND SET done = true;
    /* pesquisando o cursor */
    open pesquisa;
   
    /* Loop para todas as disciplinas */
    read_loop: LOOP
        fetch pesquisa into codigodisciplina;
		if done = true then
			leave read_loop;
		end if;
        /* Pesquisando o professor da disciplina e disponibilidade */
        select count(diaSemana) into qtde from faixa_hora inner join prof_disc_minis on faixa_hora.idPessoaFisica = prof_disc_minis.idProfessor where prof_disc_minis.idDisciplina = codigodisciplina;
       
        set contador = 0;
        WHILE contador < qtde DO
            
            set dinicio = TIME(DATE_ADD("2016-10-03 08:00:00", INTERVAL 4 hour));
            select diaSemana, inicio, fim into profdiasemana, profinicio, proffim  
            from faixa_hora inner join prof_disc_minis on faixa_hora.idPessoaFisica = prof_disc_minis.idProfessor 
            where prof_disc_minis.idDisciplina = codigodisciplina && (fim <=dinicio) limit contador,1;
           
            
			if profdiasemana != null  && profinicio != null && proffim != null  then
				insert into calendario (ano, semestre, disciplina, diasemana, horainicio, horafinal)
				values (p_ano, p_semestre, codigodisciplina, profdiasemana, profinicio, proffim);
			end if;
			SET contador = contador + 1;
        END WHILE;
    end LOOP;
    close pesquisa;
   
END;;
DELIMITER ;


/*		DML		*/

call cadastro_secretario(null,"secretario1", "endereco1", "cpf1", "rg1", 12.5,"matricula1", "nomesocial1", 12.5,13.5);
call cadastro_secretario(null,"secretario2", "endereco4", "cpf4", "rg4", 13.5,"matricula4", "nomesocial11", 13.5,14.5);
select * from secretario inner join pessoafisica on secretario.idSecretario = pessoafisica.idPessoaFisica inner join pessoa on pessoafisica.idPessoaFisica = pessoa.id;

call cadastro_professor(null,"professor1", "endereco2", "cpf2", "rg2", 1244.5,"matricula2", "nomesocial2", "UNESP");
call cadastro_professor(null,"professor2", "endereco5", "cpf5", "rg5", 1248.5,"matricula5", "nomesocial3", "UNESP");
call cadastro_professor(null,"professor3", "endereco7", "cpf7", "rg7", 1250.8,"matricula7", "nomesocial7", "USP");
call cadastro_professor(null,"professor4", "endereco8", "cpf8", "rg8", 1260.8,"matricula8", "nomesocial8", "UNICAMP");
call cadastro_professor(null,"chefe1", "endereco2", "cpf3", "rg3", 1244.6,"matricula3", "nomesocial3", "UNESP");
call cadastro_professor(null,"chefe2", "endereco6", "cpf6", "rg6", 1245.9,"matricula6", "nomesocial6", "UNICAMP");
select * from professor inner join pessoafisica on professor.idProfessor= pessoafisica.idPessoaFisica inner join pessoa on pessoafisica.idPessoaFisica = pessoa.id;

call cadastro_instituicao(null,"444444", "4444444", "fantasia1", "UNICAMP","endereco1");
call cadastro_instituicao(null,"555555", "5555555", "fantasia2", "UNESP","endereco2");
call cadastro_instituicao(null,"666666", "6666666", "fantasia3", "USP","endereco3");
select * from instituicao inner join pessoajuridica on instituicao.idInstituicao = pessoajuridica.idPessoaJuridica inner join pessoa on pessoajuridica.idPessoaJuridica = pessoa.id;

call manut_departamento (null,"departamento1", "chefe1", "UNESP");
call manut_departamento (null,"departamento2", "chefe2", "UNESP");

call manut_curso(null, "curso1", "area1", 10, "periodo1", 19,"departamento1" , "UNESP");
call manut_curso(null, "curso2", "area2", 20, "periodo2", 20,"departamento2" , "USP");
call manut_curso(null, "curso3", "area3", 30, "periodo3", 30,"departamento1" , "UNICAMP");
call manut_curso(null, "curso4", "area4", 40, "periodo4", 40,"departamento2" , "USP");

call manut_coordenador("professor1", "10-11-10","12-12-22","curso1" );
call manut_coordenador("professor2", "10-11-10","12-12-22","curso2" );

call manut_afastamento(null, "2023-10-12","2023-11-12", "professor4");

call manut_disciplina(null, "disciplina1", 10);
call manut_disciplina(null, "disciplina2", 20);
call manut_disciplina(null, "disciplina3", 30);
call manut_disciplina(null, "disciplina4", 40);

call manut_curso_disc("curso1","disciplina1" );
call manut_curso_disc("curso1","disciplina2" );
call manut_curso_disc("curso2","disciplina2" );
call manut_curso_disc("curso3","disciplina3" );
call manut_curso_disc("curso4","disciplina4" );

call manut_tiposala(null, "tiposala1");
call manut_tiposala(null, "tiposala2");

call manut_disc_tiposala("disciplina1", "tiposala1");
call manut_disc_tiposala("disciplina2", "tiposala2");

call manut_faixa_hora(null, "professor1",5,'08:00:00','12:00:00');
call manut_faixa_hora(null, "professor2",3,'09:00:00','13:00:00');
call manut_faixa_hora(null, "professor3",5,'10:00:00','14:00:00');
call manut_faixa_hora(null, "professor4",2,'06:00:00','10:00:00');

call manut_feriado(null, "independecia","2023-9-7","2023-9-7");
call manut_feriado(null, "dia do funcionario publico","2023-10-28","2023-10-28");

call manut_inst_curso("UNESP","curso1");
call manut_inst_curso("USP","curso2");
call manut_inst_curso("UNICAMP","curso3");
call manut_inst_curso("UNESP","curso4");

call manut_prerequisito( "disciplina1","disciplina2");

call manut_prof_depto( "professor1","departamento1");
call manut_prof_depto( "professor2","departamento2");
call manut_prof_depto( "professor3","departamento1");
call manut_prof_depto( "professor4","departamento2");

call manut_prof_disc_esp( "professor1","disciplina1");
call manut_prof_disc_esp( "professor2","disciplina2");
call manut_prof_disc_esp( "professor3","disciplina3");
call manut_prof_disc_esp( "professor4","disciplina4");

call manut_prof_disc_minis( "professor1","disciplina1", "curso1", 2023,2);
call manut_prof_disc_minis( "professor2","disciplina2", "curso2", 2023,1);
call manut_prof_disc_minis( "professor3","disciplina3", "curso3", 2023,2);
call manut_prof_disc_minis( "professor4","disciplina4", "curso4", 2023,1);

call manut_sala(null,"USP", "tiposala1","bloco1", 5,40);
call manut_sala(null,"UNESP", "tiposala2","bloco2", 2,50);
call manut_sala(null,"UNICAMP", "tiposala2","bloco3", 3,60);

call geracalendario(2019, 2, 1);
call geracalendario(2020, 1, 2);
call geracalendario(2021, 1, 3);
call geracalendario(2022, 2, 4);
select * from calendario;
/* SELECTS*/
/*
select * from curso;
select * from disciplina;
select * from professor;
select * from disciplina;
select * from professor inner join pessoafisica on professor.idProfessor = pessoafisica.idPessoaFisica inner join pessoa on professor.idProfessor = pessoa.id;
select * from afastamento;
select * from curso_disc;
select * from disc_tiposala;
*/

/**/